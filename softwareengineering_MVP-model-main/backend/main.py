"""pick!ture MVP — FastAPI 앱: 정적 UI 서빙 + /analyze 분석 파이프라인."""

import base64
import io
import secrets
from pathlib import Path

from fastapi import FastAPI, File, Form, Request, UploadFile
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import JSONResponse
from fastapi.staticfiles import StaticFiles
from PIL import Image, UnidentifiedImageError
from pydantic import BaseModel, Field

from backend import clip_engine, scoring

BASE_DIR = Path(__file__).resolve().parent.parent
FRONTEND_DIR = BASE_DIR / "frontend"
MAX_CANDIDATES = 30
THUMBNAIL_SIZE = (320, 320)
VOTE_LINKS: dict[str, dict] = {}


class VoteCandidate(BaseModel):
    id: str | None = None
    name: str
    thumbnail: str
    rank: int | None = None
    final: float | None = None
    vibe: float | None = None
    aesthetic: float | None = None
    comment: str | None = None


class VoteLinkRequest(BaseModel):
    title: str = "pick!ture 후보 투표"
    mood: str = ""
    candidates: list[VoteCandidate] = Field(default_factory=list)


class VoteSubmitRequest(BaseModel):
    candidate_id: str
    voter_name: str = ""

app = FastAPI(title="pick!ture MVP")

# 프론트엔드를 GitHub Pages 등 다른 도메인에서 서빙할 때 /analyze 호출을
# 허용하기 위한 CORS 설정. 데모 단계라 모든 출처를 허용한다.
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.middleware("http")
async def _no_cache(request, call_next):
    """MVP 개발 중 정적 파일이 캐시되어 옛 화면이 보이는 문제를 막는다."""
    response = await call_next(request)
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    return response


@app.on_event("startup")
def _warm_model():
    """첫 요청 지연을 줄이기 위해 서버 기동 시 모델을 미리 로드한다."""
    try:
        clip_engine.get_model()
        print("[pick!ture] CLIP model loaded")
    except Exception as exc:  # 다운로드 실패 등 — 첫 요청에서 재시도된다
        print(f"[pick!ture] model preload warning: {exc}")


def _load_image(upload: UploadFile):
    """업로드 파일을 RGB PIL 이미지로 변환. 실패하면 None."""
    try:
        img = Image.open(io.BytesIO(upload.file.read()))
        img.load()
        return img.convert("RGB")
    except (UnidentifiedImageError, OSError, ValueError):
        return None


def _thumbnail_data_uri(img: Image.Image):
    thumb = img.copy()
    thumb.thumbnail(THUMBNAIL_SIZE)
    buf = io.BytesIO()
    thumb.save(buf, format="JPEG", quality=85)
    b64 = base64.b64encode(buf.getvalue()).decode("ascii")
    return f"data:image/jpeg;base64,{b64}"


@app.post("/analyze")
async def analyze(
    reference: list[UploadFile] = File(default=[]),
    candidates: list[UploadFile] = File(default=[]),
    mood: str = Form(default=""),
    w_vibe: float = Form(default=0.8),
    threshold: float = Form(default=3.5),
):
    ref_images = [im for im in (_load_image(f) for f in reference) if im is not None]
    if not ref_images:
        return JSONResponse(
            {"error": "기준 피드 이미지를 1장 이상 업로드하세요."}, status_code=400)

    cand_pairs = []
    for f in candidates:
        img = _load_image(f)
        if img is not None:
            cand_pairs.append((f.filename or f"image_{len(cand_pairs)}", img))
    skipped = len(candidates) - len(cand_pairs)
    cand_pairs = cand_pairs[:MAX_CANDIDATES]
    if not cand_pairs:
        return JSONResponse(
            {"error": "분석 가능한 후보 이미지가 없습니다."}, status_code=400)

    w_vibe = min(max(w_vibe, 0.0), 1.0)
    threshold = min(max(threshold, 0.0), 10.0)

    ref_embeds = clip_engine.embed_images(ref_images)
    text_embed = clip_engine.embed_text(mood) if mood.strip() else None
    target = scoring.vibe_target(ref_embeds, text_embed)

    cand_images = [img for _, img in cand_pairs]
    cand_embeds = clip_engine.embed_images(cand_images)
    vibe_raw = (cand_embeds @ target).tolist()
    aes_raw = clip_engine.aesthetic_scores(cand_images)

    meta = [
        {"name": name, "thumbnail": _thumbnail_data_uri(img)}
        for name, img in cand_pairs
    ]
    ranked, filtered = scoring.rank_candidates(
        meta, vibe_raw, aes_raw, w_vibe, threshold)

    return JSONResponse({
        "ranked": ranked,
        "filtered": filtered,
        "w_vibe": round(w_vibe, 2),
        "w_aes": round(1.0 - w_vibe, 2),
        "threshold": round(threshold, 2),
        "ref_count": len(ref_images),
        "skipped": skipped,
    })


def _vote_results(link: dict):
    counts = {c["id"]: 0 for c in link["candidates"]}
    for vote in link["votes"]:
        if vote["candidate_id"] in counts:
            counts[vote["candidate_id"]] += 1
    total = sum(counts.values())
    rows = []
    for candidate in link["candidates"]:
        vote_count = counts[candidate["id"]]
        ai_score = float(candidate.get("final") or 0)
        social_score = (vote_count / total * 10.0) if total else 0.0
        rows.append({
            **candidate,
            "voteCount": vote_count,
            "voteShare": round((vote_count / total * 100.0) if total else 0.0, 1),
            "combinedScore": round((ai_score * 0.7) + (social_score * 0.3), 2),
        })
    rows.sort(key=lambda item: (item["combinedScore"], item["voteCount"]), reverse=True)
    return {"totalVotes": total, "results": rows}


@app.post("/api/votes/links")
async def create_vote_link(payload: VoteLinkRequest, request: Request):
    candidates = []
    for idx, candidate in enumerate(payload.candidates[:MAX_CANDIDATES]):
        data = candidate.model_dump()
        data["id"] = data.get("id") or f"candidate-{idx + 1}"
        candidates.append(data)
    if not candidates:
        return JSONResponse(
            {"error": "투표 링크를 만들 후보 사진이 없습니다."}, status_code=400)

    code = secrets.token_urlsafe(6)
    VOTE_LINKS[code] = {
        "code": code,
        "title": payload.title,
        "mood": payload.mood,
        "candidates": candidates,
        "votes": [],
    }
    return {
        "shareCode": code,
        "sharePath": f"/?vote={code}",
        "apiBase": str(request.base_url).rstrip("/"),
        "candidateCount": len(candidates),
    }


@app.get("/api/votes/{share_code}")
async def get_vote_link(share_code: str):
    link = VOTE_LINKS.get(share_code)
    if link is None:
        return JSONResponse({"error": "투표 링크를 찾을 수 없습니다."}, status_code=404)
    return {
        "shareCode": share_code,
        "title": link["title"],
        "mood": link["mood"],
        "candidates": link["candidates"],
        **_vote_results(link),
    }


@app.post("/api/votes/{share_code}")
async def submit_vote(share_code: str, payload: VoteSubmitRequest):
    link = VOTE_LINKS.get(share_code)
    if link is None:
        return JSONResponse({"error": "투표 링크를 찾을 수 없습니다."}, status_code=404)
    valid_ids = {candidate["id"] for candidate in link["candidates"]}
    if payload.candidate_id not in valid_ids:
        return JSONResponse({"error": "선택한 후보를 찾을 수 없습니다."}, status_code=400)
    link["votes"].append({
        "candidate_id": payload.candidate_id,
        "voter_name": payload.voter_name.strip()[:40],
    })
    return {
        "message": "투표가 반영되었습니다.",
        **_vote_results(link),
    }


# 정적 프론트엔드를 루트에 마운트한다(html=True 로 / → index.html).
# /analyze 같은 명시적 라우트가 우선하므로 충돌하지 않는다.
# GitHub Pages 배포 시에는 이 마운트가 쓰이지 않지만, HF Space 단독
# 접속이나 로컬 개발에서는 그대로 UI를 띄워 준다.
app.mount("/", StaticFiles(directory=FRONTEND_DIR, html=True), name="frontend")
