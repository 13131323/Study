import torch
import torch.nn as nn
import clip
from PIL import Image
import os
import numpy as np
import pytorch_lightning as pl

# 1. [GitHub 표준] MLP 아키텍처 정의 (ReLU 버전)
class MLP(pl.LightningModule):
    def __init__(self, input_size, xcol='emb', ycol='avg_rating'):
        super().__init__()
        self.input_size = input_size
        self.xcol = xcol
        self.ycol = ycol
        self.layers = nn.Sequential(
            nn.Linear(self.input_size, 1024),
            nn.Dropout(0.2),
            nn.Linear(1024, 128),
            nn.Dropout(0.2),
            nn.Linear(128, 64),
            nn.Dropout(0.1),
            nn.Linear(64, 16),
            nn.Linear(16, 1)
        )
    def forward(self, x): return self.layers(x)

# 2. [GitHub 표준] 정규화 함수
def normalized(a, axis=-1, order=2):
    l2 = np.atleast_1d(np.linalg.norm(a, order, axis))
    l2[l2 == 0] = 1
    return a / np.expand_dims(l2, axis)

# 환경 설정
device = "cuda" if torch.cuda.is_available() else "cpu"
# 레포지토리에서 가장 성능이 좋다고 알려진 'sac+logos+ava1-l14-linearMSE.pth' 권장
WEIGHTS_PATH = "ava+logos-l14-linearMSE.pth" 
REF_DIR, TEST_DIR = "reference", "test"

# 모델 로딩
print(f"--- {device} 장치에서 모델 로딩 중... ---")
model_clip, preprocess = clip.load("ViT-L/14", device=device)
predictor = MLP(768).to(device)
predictor.load_state_dict(torch.load(WEIGHTS_PATH, map_location=device))
predictor.eval()

def run_project_analysis():
    # A. 기준 피드 분위기(Vibe) 추출
    ref_files = [os.path.join(REF_DIR, f) for f in os.listdir(REF_DIR) if f.lower().endswith(('.jpg', '.jpeg', '.png'))]
    ref_vecs = []
    for f in ref_files:
        img = preprocess(Image.open(f)).unsqueeze(0).to(device)
        with torch.no_grad():
            v = model_clip.encode_image(img)
            ref_vecs.append(v / v.norm(dim=-1, keepdim=True))
    master_vibe = torch.mean(torch.stack(ref_vecs), dim=0)

    # B. 내 사진들 분석
    test_files = [os.path.join(TEST_DIR, f) for f in os.listdir(TEST_DIR) if f.lower().endswith(('.jpg', '.jpeg', '.png'))]
    candidates = []

    print(f"\n--- 총 {len(test_files)}장 분석 시작 ---")
    for f in test_files:
        pil_img = Image.open(f).convert("RGB")
        img_in = preprocess(pil_img).unsqueeze(0).to(device)
        
        with torch.no_grad():
            # 특징 추출
            image_features = model_clip.encode_image(img_in)
            
            # 1. Aesthetic Score (GitHub 로직)
            # 768차원 벡터를 추출한 뒤 정규화하여 MLP에 전달
            im_emb_arr = normalized(image_features.cpu().detach().numpy())
            aes_score = predictor(torch.from_numpy(im_emb_arr).to(device).float()).item()
            
            # 2. Vibe Similarity (내 피드와 얼마나 어울리는가)
            img_feat_norm = image_features / image_features.norm(dim=-1, keepdim=True)
            vibe_sim = (master_vibe @ img_feat_norm.T).item()
            
        candidates.append({'name': os.path.basename(f), 'aes': aes_score, 'vibe': vibe_sim})

    # C. 상대평가(Min-Max)로 변별력 확보
    # 모든 사진 중 꼴찌는 1점, 1등은 10점이 되게 펼쳐줌
    aes_vals = [c['aes'] for c in candidates]
    vibe_vals = [c['vibe'] for c in candidates]
    
    for c in candidates:
        a_norm = (c['aes'] - min(aes_vals)) / (max(aes_vals) - min(aes_vals) + 1e-5)
        v_norm = (c['vibe'] - min(vibe_vals)) / (max(vibe_vals) - min(vibe_vals) + 1e-5)
        
        # 7(분위기) : 3(절대미학) 가중치로 최종 점수 산출
        c['final'] = ((v_norm * 0.7) + (a_norm * 0.3)) * 9 + 1

    # 결과 출력
    candidates.sort(key=lambda x: x['final'], reverse=True)
    print(f"\n{'순위':<4} | {'파일명':<15} | {'미적 점수':<8} | {'분위기 유사도':<8} | {'최종 합산'}")
    print("-" * 75)
    for i, c in enumerate(candidates, 1):
        print(f"{i:<4} | {c['name']:<15} | {c['aes']:.2f}점      | {c['vibe']:.3f}         | {c['final']:.1f}점")

if __name__ == "__main__":
    run_project_analysis()