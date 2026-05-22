"""pick!ture MVP FastAPI app: static UI serving, analysis, and voting APIs."""

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

# Allow the static frontend to call the API from local development, GitHub Pages,
# or the Hugging Face Space demo during the MVP phase.
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.middleware("http")
async def _no_cache(request, call_next):
    """Avoid stale static files while iterating on the MVP UI."""
    response = await call_next(request)
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    return response


@app.on_event("startup")
def _warm_model():
    """Preload CLIP so the first analysis request feels less abrupt."""
    try:
        clip_engine.get_model()
        print("[pick!ture] CLIP model loaded")
    except Exception as exc:
        print(f"[pick!ture] model preload warning: {exc}")


def _load_image(upload: UploadFile):
    """Read an uploaded file as an RGB PIL image. Return None on invalid files."""
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
            {"error": "기준 피드 이미지를 1장 이상 업로드해주세요."},
            status_code=400,
        )

    cand_pairs = []
    for f in candidates:
        img = _load_image(f)
        if img is not None:
            cand_pairs.append((f.filename or f"image_{len(cand_pairs)}", img))
    skipped = len(candidates) - len(cand_pairs)
    cand_pairs = cand_pairs[:MAX_CANDIDATES]
    if not cand_pairs:
        return JSONResponse(
            {"error": "분석 가능한 후보 이미지가 없습니다."},
            status_code=400,
        )

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
    ranked, filtered = scoring.rank_candidates(meta, vibe_raw, aes_raw, w_vibe, threshold)

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
    for idx, candidate in enumerate(link["candidates"]):
        vote_count = counts[candidate["id"]]
        rows.append({
            **candidate,
            "originalOrder": idx,
            "voteCount": vote_count,
            "voteShare": round((vote_count / total * 100.0) if total else 0.0, 1),
        })

    # Primary sort: friend votes. Tie-breaker: original AI/result order.
    rows.sort(key=lambda item: (-item["voteCount"], item["originalOrder"]))
    return {"totalVotes": total, "results": rows}


@app.post("/api/votes/links")
async def create_vote_link(payload: VoteLinkRequest, request: Request):
    vote_candidates = []
    for idx, candidate in enumerate(payload.candidates[:MAX_CANDIDATES]):
        data = candidate.model_dump()
        data["id"] = data.get("id") or f"candidate-{idx + 1}"
        vote_candidates.append(data)

    if not vote_candidates:
        return JSONResponse(
            {"error": "투표 링크를 만들 후보 사진이 없습니다."},
            status_code=400,
        )

    code = secrets.token_urlsafe(6)
    VOTE_LINKS[code] = {
        "code": code,
        "title": payload.title,
        "mood": payload.mood,
        "candidates": vote_candidates,
        "votes": [],
    }
    return {
        "shareCode": code,
        "sharePath": f"/?vote={code}",
        "apiBase": str(request.base_url).rstrip("/"),
        "candidateCount": len(vote_candidates),
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


# Mount the static frontend last so explicit API routes above keep priority.
app.mount("/", StaticFiles(directory=FRONTEND_DIR, html=True), name="frontend")
