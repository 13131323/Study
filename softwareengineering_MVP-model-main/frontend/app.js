"use strict";

const DEPLOYED_API_BASE = "https://heon55-pickture.hf.space";
const LOCAL_HOSTS = new Set(["", "localhost", "127.0.0.1"]);
const API_BASE = LOCAL_HOSTS.has(window.location.hostname) ? "" : DEPLOYED_API_BASE;

const $ = (id) => document.getElementById(id);

const refInput = $("reference-input");
const candInput = $("candidate-input");
const vibeSlider = $("vibe-slider");
const thresholdSlider = $("threshold-slider");
const voteCode = new URLSearchParams(window.location.search).get("vote");

let refPreviewUrls = [];
let currentCandidates = [];
let currentVoteCode = "";

function apiUrl(path) {
  return `${API_BASE}${path}`;
}

function renderPreview(files, container, isReference) {
  container.innerHTML = "";
  if (isReference) {
    refPreviewUrls.forEach((url) => URL.revokeObjectURL(url));
    refPreviewUrls = [];
  }
  Array.from(files).forEach((file) => {
    if (!file.type.startsWith("image/")) return;
    const url = URL.createObjectURL(file);
    if (isReference) refPreviewUrls.push(url);
    const img = document.createElement("img");
    img.src = url;
    img.alt = file.name;
    container.appendChild(img);
  });
}

function scoreClass(score) {
  if (score >= 7) return "s-good";
  if (score >= 4) return "s-mid";
  return "s-bad";
}

function metricBar(label, score) {
  const safeScore = Number(score || 0);
  return `
    <div class="metric">
      <div class="metric-head"><span>${label}</span><span>${safeScore.toFixed(1)}</span></div>
      <div class="bar"><span class="${scoreClass(safeScore)}" style="width:${safeScore * 10}%"></span></div>
    </div>`;
}

function setStatus(html, isError) {
  const el = $("status");
  el.hidden = false;
  el.className = `status${isError ? " error" : ""}`;
  el.innerHTML = html;
}

function setVoteStatus(html, isError) {
  const el = $("vote-status");
  el.hidden = false;
  el.className = `status${isError ? " error" : ""}`;
  el.innerHTML = html;
}

function resultCard(item, opts) {
  const card = document.createElement("div");
  card.className = `result-card${opts.dimmed ? " dimmed" : ""}`;
  const badge = opts.dimmed
    ? `<span class="rank-badge muted">제외</span>`
    : `<span class="rank-badge${item.rank === 1 ? " top" : ""}">${item.rank}위</span>`;
  card.innerHTML = `
    <div class="photo">${badge}<img src="${item.thumbnail}" alt="${item.name}" /></div>
    <div class="card-body">
      <div class="final-score">
        <span class="num">${Number(item.final || 0).toFixed(1)}</span><span class="unit">/ 10 최종점수</span>
      </div>
      ${metricBar("피드 조화도", item.vibe)}
      ${metricBar("미학 점수", item.aesthetic)}
      <div class="comment">${item.comment || "기존 피드와의 조화를 참고해 선택해보세요."}</div>
      <button type="button" class="text-btn">피드 미리보기</button>
    </div>`;
  card.querySelector(".text-btn").addEventListener("click", (event) => {
    event.stopPropagation();
    openFeedPreview(item.thumbnail);
  });
  card.addEventListener("click", () => openFeedPreview(item.thumbnail));
  return card;
}

function renderFeedGrid(container, thumbnail) {
  container.innerHTML = "";
  const picked = document.createElement("img");
  picked.src = thumbnail;
  picked.alt = "선택한 후보 사진";
  picked.className = "picked";
  container.appendChild(picked);

  refPreviewUrls.forEach((url, index) => {
    const img = document.createElement("img");
    img.src = url;
    img.alt = `기준 피드 사진 ${index + 1}`;
    container.appendChild(img);
  });
}

function openFeedPreview(thumbnail) {
  renderFeedGrid($("feed-grid"), thumbnail);
  $("preview-modal").hidden = false;
}

function setupFeedSimulator(candidates) {
  const block = $("feed-simulator");
  const select = $("simulation-select");
  if (!candidates.length) {
    block.hidden = true;
    return;
  }
  block.hidden = false;
  select.innerHTML = "";
  candidates.forEach((item, index) => {
    const option = document.createElement("option");
    option.value = item.id;
    option.textContent = item.rank ? `${item.rank}위 - ${item.name}` : item.name || `후보 ${index + 1}`;
    select.appendChild(option);
  });
  const renderSelected = () => {
    const selected = candidates.find((item) => item.id === select.value) || candidates[0];
    renderFeedGrid($("simulation-grid"), selected.thumbnail);
  };
  select.onchange = renderSelected;
  renderSelected();
}

function normalizedCandidates(data) {
  return [...data.ranked, ...data.filtered].map((item, index) => ({
    ...item,
    id: `candidate-${index + 1}`,
  }));
}

function renderResults(data) {
  $("results").hidden = false;
  $("feature-preview").hidden = true;
  $("results-meta").textContent =
    `기준 피드 ${data.ref_count}장 · 가중치 조화도 ${data.w_vibe} / 미학 ${data.w_aes}` +
    ` · 임계값 ${data.threshold}` +
    (data.skipped ? ` · 손상/비이미지 ${data.skipped}장 제외` : "");

  currentCandidates = normalizedCandidates(data);

  const rankedList = $("ranked-list");
  rankedList.innerHTML = "";
  if (data.ranked.length === 0) {
    rankedList.innerHTML =
      `<p class="hint">임계값을 통과한 사진이 없습니다. 임계값을 낮춰 다시 시도해보세요.</p>`;
  } else {
    data.ranked.forEach((item, index) =>
      rankedList.appendChild(resultCard({ ...item, id: `candidate-${index + 1}` }, { dimmed: false })));
  }

  const filteredBlock = $("filtered-block");
  const filteredList = $("filtered-list");
  filteredList.innerHTML = "";
  if (data.filtered.length > 0) {
    filteredBlock.hidden = false;
    data.filtered.forEach((item, index) =>
      filteredList.appendChild(resultCard({ ...item, id: `filtered-${index + 1}` }, { dimmed: true })));
  } else {
    filteredBlock.hidden = true;
  }

  setupFeedSimulator(currentCandidates);
  $("vote-tools").hidden = currentCandidates.length === 0;
  $("owner-vote-results").innerHTML = "";
  $("vote-link-box").hidden = true;
  currentVoteCode = "";
  $("results").scrollIntoView({ behavior: "smooth" });
}

function renderVoteResults(container, payload) {
  if (!payload || !payload.results) {
    container.innerHTML = "";
    return;
  }
  const total = payload.totalVotes || 0;
  container.innerHTML = `
    <div class="vote-summary">총 ${total}표 · 통합 점수는 AI 70% + 투표 30% 기준입니다.</div>
    ${payload.results.map((item, index) => `
      <div class="vote-row">
        <img src="${item.thumbnail}" alt="${item.name}" />
        <div class="vote-row-body">
          <strong>${index + 1}. ${item.name}</strong>
          <span>${item.voteCount}표 (${item.voteShare}%) · 통합 ${Number(item.combinedScore || 0).toFixed(1)} / 10</span>
          <div class="bar"><span class="s-good" style="width:${Math.min(item.voteShare, 100)}%"></span></div>
        </div>
      </div>`).join("")}`;
}

async function createVoteLink() {
  if (!currentCandidates.length) {
    setStatus("투표 링크를 만들 후보 사진이 없습니다.", true);
    return;
  }
  const btn = $("create-vote-link");
  btn.disabled = true;
  btn.textContent = "생성 중...";
  try {
    const res = await fetch(apiUrl("/api/votes/links"), {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        title: "pick!ture 후보 사진 투표",
        mood: $("mood-input").value,
        candidates: currentCandidates,
      }),
    });
    const data = await res.json();
    if (!res.ok) throw new Error(data.error || "투표 링크 생성에 실패했습니다.");
    currentVoteCode = data.shareCode;
    const shareUrl = `${window.location.origin}${window.location.pathname}?vote=${data.shareCode}`;
    $("vote-link-output").value = shareUrl;
    $("vote-link-box").hidden = false;
    await refreshOwnerVoteResults();
  } catch (err) {
    setStatus(err.message, true);
  } finally {
    btn.disabled = false;
    btn.textContent = "투표 링크 생성";
  }
}

async function refreshOwnerVoteResults() {
  if (!currentVoteCode) return;
  const res = await fetch(apiUrl(`/api/votes/${currentVoteCode}`));
  const data = await res.json();
  if (!res.ok) {
    $("owner-vote-results").innerHTML = `<p class="hint">${data.error || "투표 결과를 불러오지 못했습니다."}</p>`;
    return;
  }
  renderVoteResults($("owner-vote-results"), data);
}

function renderVotePage(data) {
  $("vote-title").textContent = data.title || "사진 투표";
  $("vote-subtitle").textContent =
    data.mood ? `요청 분위기: ${data.mood}` : "가장 피드에 잘 어울리는 후보 사진을 선택해주세요.";
  const wrap = $("vote-candidates");
  wrap.innerHTML = "";
  data.candidates.forEach((item) => {
    const card = document.createElement("button");
    card.type = "button";
    card.className = "vote-card";
    card.innerHTML = `
      <img src="${item.thumbnail}" alt="${item.name}" />
      <span class="vote-card-title">${item.name}</span>
      <span class="vote-card-meta">AI ${Number(item.final || 0).toFixed(1)} · 조화도 ${Number(item.vibe || 0).toFixed(1)}</span>`;
    card.addEventListener("click", () => submitPublicVote(data.shareCode, item.id));
    wrap.appendChild(card);
  });
}

async function loadVotePage(code) {
  $("analyze-form").hidden = true;
  $("results").hidden = true;
  $("vote-screen").hidden = false;
  setVoteStatus(`<span class="spinner"></span>투표 후보를 불러오는 중입니다.`, false);
  try {
    const res = await fetch(apiUrl(`/api/votes/${code}`));
    const data = await res.json();
    if (!res.ok) throw new Error(data.error || "투표 링크를 불러오지 못했습니다.");
    $("vote-status").hidden = true;
    renderVotePage(data);
  } catch (err) {
    setVoteStatus(err.message, true);
  }
}

async function submitPublicVote(code, candidateId) {
  setVoteStatus(`<span class="spinner"></span>투표를 반영하는 중입니다.`, false);
  try {
    const res = await fetch(apiUrl(`/api/votes/${code}`), {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ candidate_id: candidateId }),
    });
    const data = await res.json();
    if (!res.ok) throw new Error(data.error || "투표를 저장하지 못했습니다.");
    setVoteStatus("투표가 반영되었습니다. 참여해주셔서 감사합니다.", false);
    renderVoteResults($("vote-status"), data);
    $("vote-candidates").querySelectorAll("button").forEach((button) => {
      button.disabled = true;
    });
  } catch (err) {
    setVoteStatus(err.message, true);
  }
}

if (refInput && candInput) {
  refInput.addEventListener("change", () =>
    renderPreview(refInput.files, $("reference-preview"), true));
  candInput.addEventListener("change", () =>
    renderPreview(candInput.files, $("candidate-preview"), false));

  vibeSlider.addEventListener("input", () => {
    const v = parseFloat(vibeSlider.value);
    $("weight-label").textContent = `${v.toFixed(2)} / ${(1 - v).toFixed(2)}`;
  });
  thresholdSlider.addEventListener("input", () => {
    $("threshold-label").textContent = parseFloat(thresholdSlider.value).toFixed(1);
  });

  $("analyze-form").addEventListener("submit", async (e) => {
    e.preventDefault();
    if (refInput.files.length === 0) {
      setStatus("기준 피드 사진을 1장 이상 올려주세요.", true);
      return;
    }
    if (candInput.files.length === 0) {
      setStatus("후보 사진을 1장 이상 올려주세요.", true);
      return;
    }

    const form = new FormData();
    Array.from(refInput.files).forEach((file) => form.append("reference", file));
    Array.from(candInput.files).forEach((file) => form.append("candidates", file));
    form.append("mood", $("mood-input").value);
    form.append("w_vibe", vibeSlider.value);
    form.append("threshold", thresholdSlider.value);

    const btn = $("analyze-btn");
    btn.disabled = true;
    $("results").hidden = true;
    setStatus(
      `<span class="spinner"></span>AI가 사진을 분석 중입니다. CPU 추론이라 사진 수에 따라 시간이 걸릴 수 있어요.`,
      false);

    try {
      const res = await fetch(apiUrl("/analyze"), { method: "POST", body: form });
      const data = await res.json();
      if (!res.ok) {
        setStatus(data.error || "분석 중 오류가 발생했습니다.", true);
        return;
      }
      $("status").hidden = true;
      renderResults(data);
    } catch (err) {
      setStatus("서버에 연결하지 못했습니다: " + err.message, true);
    } finally {
      btn.disabled = false;
    }
  });

  $("modal-close").addEventListener("click", () => ($("preview-modal").hidden = true));
  $("preview-modal").addEventListener("click", (e) => {
    if (e.target.id === "preview-modal") $("preview-modal").hidden = true;
  });
  $("create-vote-link").addEventListener("click", createVoteLink);
  $("refresh-vote-results").addEventListener("click", refreshOwnerVoteResults);
}

if (voteCode) {
  $("feature-preview").hidden = true;
  loadVotePage(voteCode);
}
