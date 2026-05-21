import torch
import clip
from PIL import Image
import os

# 1. 환경 설정 및 모델 로드
device = "cuda" if torch.cuda.is_available() else "cpu"
model, preprocess = clip.load("ViT-B/32", device=device)

# 2. 분석 기준 설정
REF_DIR = "reference"  # 기준 사진 10장 폴더
TEST_DIR = "test"       # 테스트 사진 폴더

# 인플루언서 피드 분석을 통해 도출한 핵심 해시태그 20개
hashtags = [
    "aesthetic", "natural light", "sunlight", "soft", "clear", 
    "pure", "bright", "minimalism", "korean style", 
    "outfit of the day", "daily look", "portrait", "selfie", "moody", 
    "trending", "beige"
]

def get_features():
    # A. 이미지 기준 벡터 생성 (10장 평균)
    ref_files = [os.path.join(REF_DIR, f) for f in os.listdir(REF_DIR) if f.lower().endswith(('.jpg', '.jpeg', '.png'))]
    if not ref_files:
        raise FileNotFoundError(f"{REF_DIR} 폴더에 사진이 없어!")
        
    ref_vectors = []
    print(f"--- [Step 1] 기준 사진 {len(ref_files)}장 분석 중... ---")
    for f in ref_files:
        img = preprocess(Image.open(f)).unsqueeze(0).to(device)
        with torch.no_grad():
            feat = model.encode_image(img)
            feat /= feat.norm(dim=-1, keepdim=True)
            ref_vectors.append(feat)
    
    master_img_vec = torch.mean(torch.stack(ref_vectors), dim=0)
    master_img_vec /= master_img_vec.norm(dim=-1, keepdim=True)

    # B. 텍스트 기준 벡터 생성 (20개 해시태그 평균)
    print(f"--- [Step 2] 핵심 해시태그 {len(hashtags)}개 분석 중... ---")
    text_tokens = clip.tokenize(hashtags).to(device)
    with torch.no_grad():
        text_feats = model.encode_text(text_tokens)
        text_feats /= text_feats.norm(dim=-1, keepdim=True)
        master_txt_vec = text_feats.mean(dim=0, keepdim=True)
        master_txt_vec /= master_txt_vec.norm(dim=-1, keepdim=True)
        
    return master_img_vec, master_txt_vec

def run_test(master_img_vec, master_txt_vec):
    test_files = [os.path.join(TEST_DIR, f) for f in os.listdir(TEST_DIR) if f.lower().endswith(('.jpg', '.jpeg', '.png'))]
    if not test_files:
        print(f"{TEST_DIR} 폴더에 테스트할 사진이 없어!")
        return

    results = []
    print(f"\n--- [Step 3] '{len(test_files)}장' 후보 사진 취향 분석 시작 ---\n")
    
    for f in test_files:
        img = preprocess(Image.open(f)).unsqueeze(0).to(device)
        with torch.no_grad():
            img_vec = model.encode_image(img)
            img_vec /= img_vec.norm(dim=-1, keepdim=True)
            
            # 유사도 계산
            sim_img = (master_img_vec @ img_vec.T).item()
            sim_txt = (master_txt_vec @ img_vec.T).item()
            
            # 최종 점수 산출 (이미지 40% + 텍스트 60%)
            # 텍스트 비중을 높여 '감성 키워드'가 점수를 방어하게 세팅
            final_sim = (sim_img * 0.4) + (sim_txt * 0.6)
            
            # 10점 만점 환산 (시각적 보정 포함)
            display_score = max(1.0, min(10.0, (final_sim - 0.22) / (0.45 - 0.22) * 9 + 1))
            results.append((f, sim_img, sim_txt, display_score))

    # 점수 높은 순 정렬
    results.sort(key=lambda x: x[3], reverse=True)
    
    print(f"{'Rank':<4} | {'파일명':<15} | {'Img Sim':<8} | {'Txt Sim':<8} | {'Score'}")
    print("-" * 70)
    for i, res in enumerate(results, 1):
        print(f"{i:<4} | {os.path.basename(res[0]):<15} | {res[1]:.4f} | {res[2]:.4f} | {res[3]:.1f}점")

# 메인 프로세스 실행
if __name__ == "__main__":
    try:
        m_img, m_txt = get_features()
        run_test(m_img, m_txt)
    except Exception as e:
        print(f"❌ 오류가 발생했어: {e}")