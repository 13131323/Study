import fitz

doc = fitz.open("솦공 요구 사항 분석.pdf")

text = ""
for page in doc:
    text += page.get_text()

open("requirements.md", "w", encoding="utf-8").write(text)