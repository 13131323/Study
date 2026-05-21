import os
import torch
import torch.nn as nn
import numpy as np
import clip
import pytorch_lightning as pl
from PIL import Image

# ==========================================
# 1. MLP 모델 정의 (GitHub 표준 구조)
# ==========================================
class MLP(pl.LightningModule):
    def __init__(self, input_size):
        super().__init__()
        self.input_size = input_size
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

    def forward(self, x):
        return self.layers(x)

# ==========================================
# 2. 유틸리티 함수
# ==========================================
def l2_normalized(a, axis=-1, order=2):
    """특징 벡터를 L2 정규화하는 함수"""
    l2 = np.atleast_1d(np.linalg.norm(a, order, axis))
    l2[l2 == 0] = 1
    return a / np.expand_dims(l2, axis)

# ==========================================
# 3. 메인 예측 프로세스
# ==========================================
def predict_aesthetic(img_path, model_path):
    device = "cuda" if torch.cuda.is_available() else "cpu"
    print(f"--- [{device}] 장치에서 분석 시작 ---")

    # A. CLIP 모델 로드 (ViT-L/14 버전 고정)
    clip_model, preprocess = clip.load("ViT-L/14", device=device)

    # B. Aesthetic Predictor(MLP) 로드
    # ViT-L/14의 임베딩 크기는 768입니다.
    model = MLP(768).to(device)
    state_dict = torch.load(model_path, map_location=device)
    model.load_state_dict(state_dict)
    model.eval()

    # C. 이미지 전처리 및 특징 추출
    pil_image = Image.open(img_path).convert("RGB")
    image_input = preprocess(pil_image).unsqueeze(0).to(device)

    with torch.no_grad():
        # CLIP을 이용한 이미지 임베딩 추출
        image_features = clip_model.encode_image(image_input)
        
        # 특징 벡터 정규화 (CPU에서 numpy로 처리 후 다시 Tensor로)
        im_emb_arr = l2_normalized(image_features.cpu().numpy())
        feat_tensor = torch.from_numpy(im_emb_arr).to(device).float()
        
        # 최종 점수 예측
        prediction = model(feat_tensor)

    return prediction.item()

# ==========================================
# 4. 실행부
# ==========================================
if __name__ == "__main__":
    # 파일 경로 설정 (이 두 파일이 코드와 같은 폴더에 있어야 함)
    TARGET_IMG = "test/4.jpg" 
    MODEL_WEIGHTS = "ava+logos-l14-linearMSE.pth"

    if os.path.exists(TARGET_IMG) and os.path.exists(MODEL_WEIGHTS):
        score = predict_aesthetic(TARGET_IMG, MODEL_WEIGHTS)
        print(f"\n✅ 분석 완료!")
        print(f"📸 이미지: {TARGET_IMG}")
        print(f"⭐️ Aesthetic Score: {score:.4f}")
    else:
        print("❌ 에러: 이미지 파일 또는 .pth 모델 파일을 찾을 수 없습니다.")