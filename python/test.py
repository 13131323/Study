import torch
import clip
from PIL import Image
import os
import torch.nn.functional as F

# 1. 환경 설정
device = "cuda" if torch.cuda.is_available() else "cpu"
model, preprocess = clip.load("ViT-B/32", device=device)

def get_vector(image_path):
    """이미지를 넣으면 512차원 특징 벡터를 반환하는 함수"""
    image = preprocess(Image.open(image_path)).unsqueeze(0).to(device)
    with torch.no_grad():
        features = model.encode_image(image)
        features /= features.norm(dim=-1, keepdim=True) # 정규화
    return features

# 2. 기준 피드(10장) 분석 및 평균 벡터 생성
ref_dir = "reference"
ref_files = [os.path.join(ref_dir, f) for f in os.listdir(ref_dir) if f.endswith(('.jpg', '.png', '.jpeg'))]

print(f"--- {len(ref_files)}장의 사진으로 취향 DNA 분석 중... ---")
ref_vectors = []
for f in ref_files:
    ref_vectors.append(get_vector(f))

# 10개 벡터의 평균 계산 (Master Vibe Vector)
# 수식: V_ref = (1/n) * Σ V_i
master_vibe_vector = torch.mean(torch.stack(ref_vectors), dim=0)
master_vibe_vector /= master_vibe_vector.norm(dim=-1, keepdim=True) # 다시 한번 정규화

# 3. 테스트 사진(5장) 비교 분석
test_dir = "test"
test_files = [os.path.join(test_dir, f) for f in os.listdir(test_dir) if f.endswith(('.jpg', '.png', '.jpeg'))]

results = []
print(f"--- {len(test_files)}장의 후보 사진 점수 매기는 중... ---\n")

for f in test_files:
    test_vec = get_vector(f)
    # 코사인 유사도 계산
    similarity = (master_vibe_vector @ test_vec.T).item()
    
    # 0~1 사이의 유사도를 1~10점 사이로 보기 좋게 매핑
    # (보통 0.4이하가 하위권, 0.8이상이 상위권인 점을 감안)
    score = max(1, min(10, (similarity - 0.4) / (0.9 - 0.4) * 9 + 1))
    results.append((f, similarity, score))

# 4. 결과 출력 (점수 높은 순으로 정렬)
results.sort(key=lambda x: x[1], reverse=True)

print(f"{'파일명':<20} | {'유사도':<10} | {'추천 점수'}")
print("-" * 50)
for res in results:
    print(f"{os.path.basename(res[0]):<20} | {res[1]:.4f} | {res[2]:.1f}점")