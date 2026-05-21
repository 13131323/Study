# AGENTS.md

## Purpose of this file

This file gives Codex project-specific instructions for the `pick!ture` repository.

Before changing code, Codex must understand the project requirements from the documents in `docs/`.
The project is an AI-based SNS photo auto-selection service called **pick!ture**.

## Required reading order

Before implementing, modifying, or deleting any code, read these files first if they exist:

1. `docs/project_plan.md`
2. `docs/requirements.md`
3. `README.md`
4. Existing source code under `backend/`
5. Existing source code under `frontend/`

If only PDF files exist, do **not** guess from filenames alone. Ask the user to provide converted Markdown/TXT versions, or create converted Markdown files from the PDFs first.

Expected original documents:

- `docs/소프트웨어공학_과제기획서_v3.pdf`
- `docs/솦공 요구 사항 분석.pdf`

Recommended converted files:

- `docs/project_plan.md`
- `docs/requirements.md`

## Project summary

`pick!ture` is an AI-based SNS photo curation service.
The system helps users choose the best photo to upload by combining AI-based quantitative analysis and social feedback.

The main product idea is:

- A user uploads multiple candidate photos.
- A user uploads 5 to 10 existing feed photos as a reference group.
- The AI analyzes photo quality and feed-style similarity.
- The system recommends Top-N photos.
- The user can preview how a selected photo fits into the feed.
- The user can share a voting link with friends.
- Voting results can supplement the AI recommendation.

The product direction is **“The Best Fit, Not Just a High Score.”**
Do not design the service as a harsh beauty/appearance scoring app. Treat scores as personal branding and feed-curation assistance.

## Core goals

The system should support:

1. Automatic photo recommendation
   - Recommend Top-N photos based on the user's existing feed style and preference.

2. Aesthetic quantification
   - Convert subjective photo quality into explainable objective scores.

3. Feed curation automation
   - Consider the visual consistency of the overall SNS feed.

4. Decision support
   - Combine AI recommendation with user participation and friend voting.

5. Privacy-aware processing
   - Follow a Privacy by Design approach.
   - Delete original uploaded images after feature extraction/vectorization when possible.

## Target users

Primary users:

- Personal branding users
- Creators
- Influencers
- Freelancers
- One-person businesses
- Photographers
- Users who care about SNS feed consistency and reaction metrics

Secondary users:

- PR/marketing workers
- Users managing a public image or brand tone

Auxiliary users:

- Friends or acquaintances who participate in voting through a shared link

## Functional requirements

Implement features according to the following requirement groups.

### F1. Image upload and preprocessing

The system should allow users to:

- Upload up to 30 candidate images.
- Upload text keywords describing the desired mood.
- Upload 5 to 10 existing feed images as a reference group.
- Store and manage image metadata required for analysis.
- Perform hard filtering on technically poor photos, such as blurred or noisy images.

Important:
- The reference group is required for feed-style similarity.
- Instagram crawling or direct Instagram API-based data collection should not be assumed.
- The MVP should use direct user upload instead.

### F2. AI-based photo analysis and recommendation

The system should calculate:

1. Aesthetic Score (`S_aes`)
   - Measures the objective quality of the photo.
   - May consider composition, rule of thirds, color histogram, sharpness, noise, and similar technical/aesthetic indicators.

2. Vibe Score (`S_vibe`)
   - Measures similarity between the uploaded candidate photo and the user's reference feed.
   - Should be based on vector embeddings and cosine similarity.

3. Final Score
   - Default formula:

```text
Final Score = 0.8 * S_vibe + 0.2 * S_aes
```

   - The final result should be converted to a 10-point scale when displayed.
   - Rank photos by Final Score.
   - The default priority is feed consistency over standalone photo beauty.

4. Explainable feedback
   - For recommended photos, provide strengths, weaknesses, and understandable feedback.
   - Avoid returning only raw numbers.

### F3. Feed optimization and simulation

The system should provide:

- Feed preview.
- Simulation of how a selected photo would look when added to the user's existing feed.
- A way to check whether the photo maintains feed tone and mood.

### F4. Social feedback and user participation

The system should provide:

- Voting link generation.
- External friend/acquaintance voting.
- Voting result collection.
- Combined result display where social feedback can support the AI result.
- User-customizable weights, such as prioritizing color, composition, or vibe.

## Non-functional requirements

### Performance

Target:

- Analyze 30 images within 5 seconds.

Optimization strategies may include:

- Batch inference
- Caching
- Model light-weighting
- ONNX/TensorRT where applicable
- Image resizing/compression before upload or inference

For MVP implementation, do not over-engineer GPU infrastructure unless explicitly requested.

### Scalability and maintainability

The architecture should keep major modules independent:

- Frontend
- Backend/main server
- AI analysis server/module
- Database/storage

AI analysis, recommendation, and voting should be modular so that each can be changed independently.

### Reliability

The system should avoid one failure breaking all features.

For example:

- Image upload
- AI API
- Feed preview
- Voting

should be separated enough that the project remains maintainable.

### Security and privacy

The system must:

- Protect user data.
- Avoid unauthorized API access.
- Use authentication/authorization for protected APIs.
- Avoid retaining original images longer than needed.
- Prefer storing vectors/metadata over original images after analysis.
- Clearly separate temporary image files from persistent metadata.

### Usability

The user should be able to get recommendation results in a simple flow.

Target UX:

- Within 3 major steps from entering the service, the user should reach a recommendation result.
- UI should be mobile-friendly.
- Results should be visually understandable.

### Ethics

Do not implement the service as a harmful appearance-ranking system.

Keep these principles:

- Avoid encouraging unhealthy comparison.
- Present scores as feed-fit and personal branding references.
- Avoid claims about universal beauty.
- Monitor or reduce model bias where possible.

## Architecture guidance

Expected architecture:

```text
frontend/
backend/
docs/
```

Potential service separation:

```text
Frontend UI
  -> Backend/Main Server
      -> AI Analysis Module or AI Server
      -> Database/Storage
      -> Voting Module
```

Backend responsibilities may include:

- Image upload API
- Reference feed management API
- Analysis request API
- Recommendation result API
- Voting link API
- Voting result API
- User/project/session management
- Metadata persistence

AI module/server responsibilities may include:

- Image preprocessing
- Feature extraction/vectorization
- Aesthetic score calculation
- Vibe score calculation
- Final score calculation
- Top-N ranking
- Feedback generation

Frontend responsibilities may include:

- Image upload UI
- Reference feed upload UI
- Mood keyword input
- Analysis progress/loading state
- Ranking dashboard
- Photo feedback display
- Feed preview
- Voting link sharing
- Voting page
- Voting result display

## Suggested API concepts

Do not blindly create these if existing APIs already differ.
First inspect the existing backend code.

Possible API groups:

```text
POST /api/images/upload
POST /api/reference-groups
POST /api/analysis/requests
GET  /api/analysis/results/{id}
POST /api/votes/links
GET  /api/votes/{shareCode}
POST /api/votes/{shareCode}
GET  /api/votes/results/{shareCode}
```

## Suggested domain concepts

Do not introduce all entities unless needed.
Use the existing project structure first.

Possible domain objects:

- `User`
- `Image`
- `CandidateImage`
- `ReferenceImage`
- `ReferenceGroup`
- `AnalysisRequest`
- `AnalysisResult`
- `PhotoScore`
- `VoteLink`
- `Vote`
- `FeedPreview`

Possible score fields:

- `aestheticScore`
- `vibeScore`
- `finalScore`
- `rank`
- `strengths`
- `weaknesses`
- `feedback`

## Testing expectations

When implementing or changing behavior, consider these test cases.

### Functional tests

- Low aesthetic score image is filtered out before Stage 2.
- Candidate image very different from reference feed receives a low Vibe Score.
- Final Score is calculated using the correct weight formula.
- Weight customization changes ranking results.
- Voting link can be generated.
- External user can vote.
- Vote result appears in dashboard/result view.

### Performance/security tests

- 30-image analysis target should be considered.
- Original image deletion after vectorization should be verified where implemented.
- Reference group CRUD should preserve data integrity.

### Exception tests

- Non-image file upload should not crash the system.
- Corrupted image file should return a clear error.
- If fewer images than Top-N are uploaded, return the best available ranking from uploaded images.
- If reference images are missing, guide the user to upload reference feed images instead of silently producing random results.

## Coding rules

Follow these rules when working in this repository:

1. Read relevant files before editing.
2. Do not rewrite the whole project unless the user explicitly asks.
3. Keep existing folder structure and naming conventions when possible.
4. Make small, reviewable changes.
5. Do not delete existing code without explaining why.
6. Do not invent requirements that are not in the documents.
7. If a requirement is ambiguous, ask the user before implementing.
8. Prefer clear, simple MVP implementation over unnecessary architecture complexity.
9. Keep frontend/backend/AI responsibilities separated.
10. Add comments only where they clarify non-obvious logic.

## AI/model implementation rules

When implementing AI logic for MVP:

- It is acceptable to start with a mock/scaffold AI module if real model integration is not ready.
- Clearly label mock logic as temporary.
- Keep the interface stable so the real model can replace the mock later.
- Do not hardcode final demo values in production paths.
- Keep the scoring pipeline explicit:

```text
input images
-> preprocessing
-> hard filtering
-> aesthetic score
-> vibe score
-> final score
-> ranking
-> feedback/result
```

## Data policy

Do not build features based on Instagram crawling.

Use this policy:

- Users directly upload reference feed images.
- Users directly upload candidate images.
- Original image files should be temporary when possible.
- Persist only necessary metadata, vectors, scores, and result records.
- If persistent original storage is required for MVP demo, mark it clearly and isolate it for later removal.

## UX writing rules

Use supportive language.

Good:

- “이 사진은 기존 피드 분위기와 잘 어울려요.”
- “색감은 잘 맞지만 구도 점수가 낮아 보완이 필요해요.”
- “AI 추천과 지인 투표를 함께 참고해 최종 선택해보세요.”

Avoid:

- “이 사진은 못생겼습니다.”
- “점수가 낮으니 올리지 마세요.”
- “당신의 사진은 실패입니다.”

## Done definition

A task is done only when:

1. The changed files match the documented requirement.
2. The code runs or the expected reason for not running is clearly stated.
3. Relevant tests or manual verification steps are provided.
4. The change does not break unrelated existing behavior.
5. Any assumptions are written clearly.

## First prompt recommendation for Codex

When starting a new Codex session, use a prompt like this:

```text
Read AGENTS.md, docs/project_plan.md, and docs/requirements.md first.
Then inspect the existing frontend/backend structure.
Do not modify code yet.
Summarize the current project structure, implemented features, missing features, and the safest next task.
```

## Important reminder

This is a software engineering project, so preserve traceability between:

- requirements
- implementation
- test cases

When possible, mention requirement IDs such as F1.1, F2.3, NF1.1, or TC-F-03 in commit messages, comments, or task summaries.
