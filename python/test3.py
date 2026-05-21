import torch
import clip
from PIL import Image
import os

# 1. 환경 설정 및 모델 로드
device = "cuda" if torch.cuda.is_available() else "cpu"
model, preprocess = clip.load("ViT-B/32", device=device)

# 2. 분석 기준 설정
REF_DIR = "reference"
TEST_DIR = "test"

# [지향] 맑고 투명한 분위기 해시태그
hashtags_pos = [
    "aesthetic", "natural light", "sunlight", "soft", "clear", 
    "pure", "bright", "minimalism", "feminine", "korean style", 
    "outfit of the day", "daily look", "portrait", "selfie", "moody", 
    "trending", "flower", "cake", "white", "beige"
]

# [지양] 하지만 점수를 너무 깎지는 않을 정도의 네거티브 키워드
hashtags_neg = [
    "dark", "rugged", "rough", "heavy", "aggressive", "masculine", "low key"
]

def get_master_vectors():
    # A. 이미지 기준 벡터
    ref_files = [os.path.join(REF_DIR, f) for f in os.listdir(REF_DIR) if f.lower().endswith(('.jpg', '.jpeg', '.png'))]
    ref_vectors = []
    print(f"--- [Step 1] 기준 사진 분석 중... ---")
    for f in ref_files:
        img = preprocess(Image.open(f)).unsqueeze(0).to(device)
        with torch.no_grad():
            feat = model.encode_image(img)
            feat /= feat.norm(dim=-1, keepdim=True)
            ref_vectors.append(feat)
    master_img_vec = torch.mean(torch.stack(ref_vectors), dim=0)
    master_img_vec /= master_img_vec.norm(dim=-1, keepdim=True)

    # B. 긍정/부정 텍스트 벡터
    pos_tokens = clip.tokenize(hashtags_pos).to(device)
    neg_tokens = clip.tokenize(hashtags_neg).to(device)
    with torch.no_grad():
        pos_feats = model.encode_text(pos_tokens).mean(dim=0, keepdim=True)
        neg_feats = model.encode_text(neg_tokens).mean(dim=0, keepdim=True)
        pos_feats /= pos_feats.norm(dim=-1, keepdim=True)
        neg_feats /= neg_feats.norm(dim=-1, keepdim=True)
        
    return master_img_vec, pos_feats, neg_feats

def run_balanced_test(m_img, m_pos, m_neg):
    test_files = [os.path.join(TEST_DIR, f) for f in os.listdir(TEST_DIR) if f.lower().endswith(('.jpg', '.jpeg', '.png'))]
    results = []
    print(f"\n--- [Final] 밸런스 조정 분석 시작 (순한맛) ---\n")

    for f in test_files:
        img = preprocess(Image.open(f)).unsqueeze(0).to(device)
        with torch.no_grad():
            img_vec = model.encode_image(img)
            img_vec /= img_vec.norm(dim=-1, keepdim=True)
            
            sim_img = (m_img @ img_vec.T).item()
            sim_pos = (m_pos @ img_vec.T).item()
            sim_neg = (m_neg @ img_vec.T).item()
            
            # --- 가중치 밸런스 패치 핵심 ---
            # 이미지(0.4) + 긍정텍스트(0.5) - 부정텍스트(0.1)
            # 부정적인 요소를 '감점'이 아닌 '미세 조정' 수준으로 변경
            final_val = (sim_img * 0.4) + (sim_pos * 0.5) - (sim_neg * 0.1)
            
            # 10점 만점 환산 시 하한선을 높여서 점수 보정
            # 0.18 정도만 넘어도 1점을 넘기도록 설정
            display_score = max(1.0, min(10.0, (final_val - 0.18) / (0.42 - 0.18) * 8 + 2))
            results.append((f, sim_img, sim_pos, sim_neg, display_score))

    results.sort(key=lambda x: x[4], reverse=True)
    
    print(f"{'Rank':<4} | {'파일명':<12} | {'ImgSim':<7} | {'PosSim':<7} | {'NegSim':<7} | {'Score'}")
    print("-" * 75)
    for i, res in enumerate(results, 1):
        print(f"{i:<4} | {os.path.basename(res[0]):<12} | {res[1]:.3f} | {res[2]:.3f} | {res[3]:.3f} | {res[4]:.1f}점")

if __name__ == "__main__":
    try:
        m_img, m_pos, m_neg = get_master_vectors()
        run_balanced_test(m_img, m_pos, m_neg)
    except Exception as e:
        print(f"❌ 오류: {e}")