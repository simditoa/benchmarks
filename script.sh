#!/usr/bin/env bash
set -euo pipefail

# DigitalOcean/AWS/Ubuntu bootstrap script for the itoa benchmarks suite.
#
# Detects AVX-512 IFMA + VBMI on the host and enables those flags so simditoa's
# AVX-512 code path is included. Falls back to a portable scalar build otherwise.
#
# Usage:
#   curl -fsSL <raw-script-url> | bash
#
# Optional environment overrides:
#   REPO_URL=https://github.com/simditoa/benchmarks.git
#   BRANCH=main
#   WORKDIR=${HOME}/benchmarks
#   BUILD_TYPE=Release
#   EXTRA_CXX_FLAGS=""    # overrides auto-detected -march flags
#   FORCE_AVX512=0        # set to 1 to force AVX-512 flags even if cpuinfo lookup fails

REPO_URL="${REPO_URL:-https://github.com/simditoa/benchmarks.git}"
BRANCH="${BRANCH:-main}"
WORKDIR="${WORKDIR:-${HOME}/benchmarks}"
BUILD_TYPE="${BUILD_TYPE:-Release}"
EXTRA_CXX_FLAGS="${EXTRA_CXX_FLAGS:-}"
FORCE_AVX512="${FORCE_AVX512:-0}"

if [[ "$(uname -s)" != "Linux" ]]; then
  echo "This bootstrap script is intended for Linux hosts." >&2
  exit 1
fi

if ! command -v apt-get >/dev/null 2>&1; then
  echo "This bootstrap script expects an apt-based distro such as Ubuntu." >&2
  exit 1
fi

if [[ "${EUID}" -eq 0 ]]; then
  SUDO=()
else
  SUDO=(sudo)
fi

echo "==> Installing build dependencies..."
"${SUDO[@]}" apt-get update
"${SUDO[@]}" apt-get install -y --no-install-recommends \
  ca-certificates \
  build-essential \
  cmake \
  git

# ---- Detect AVX-512 IFMA + VBMI support --------------------------------------
HAS_AVX512_IFMA=0
HAS_AVX512_VBMI=0
if grep -q -E '^flags\s*:.*\bavx512ifma\b' /proc/cpuinfo 2>/dev/null; then
  HAS_AVX512_IFMA=1
fi
if grep -q -E '^flags\s*:.*\bavx512vbmi\b' /proc/cpuinfo 2>/dev/null; then
  HAS_AVX512_VBMI=1
fi

AUTO_FLAGS=""
if [[ -z "${EXTRA_CXX_FLAGS}" ]]; then
  if [[ "${HAS_AVX512_IFMA}" -eq 1 && "${HAS_AVX512_VBMI}" -eq 1 ]] || [[ "${FORCE_AVX512}" -eq 1 ]]; then
    AUTO_FLAGS="-mavx512f -mavx512dq -mavx512bw -mavx512vl -mavx512ifma -mavx512vbmi"
    echo "==> Detected AVX-512 IFMA + VBMI: enabling AVX-512 build (${AUTO_FLAGS})"
  else
    echo "==> AVX-512 IFMA + VBMI not detected: building scalar fallback only"
    echo "    (set FORCE_AVX512=1 to override, or pass EXTRA_CXX_FLAGS explicitly)"
  fi
else
  echo "==> Using user-provided EXTRA_CXX_FLAGS=${EXTRA_CXX_FLAGS}"
fi

CXX_FLAGS="${EXTRA_CXX_FLAGS:-${AUTO_FLAGS}}"

echo "==> Preparing workspace: ${WORKDIR}"
mkdir -p "${WORKDIR}"
cd "${WORKDIR}"

if [[ -d benchmarks/.git ]]; then
  echo "==> Updating existing repository..."
  git -C benchmarks fetch --all --prune
  git -C benchmarks switch "${BRANCH}"
  git -C benchmarks pull --ff-only
else
  echo "==> Cloning ${REPO_URL} (${BRANCH})..."
  git clone --branch "${BRANCH}" --single-branch "${REPO_URL}" benchmarks
fi

cd benchmarks

if [[ -d build ]]; then
  echo "==> Removing previous build directory to apply fresh flags..."
  rm -rf build
fi

echo "==> Configuring (BUILD_TYPE=${BUILD_TYPE}, CXX_FLAGS='${CXX_FLAGS}')..."
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
  -DCMAKE_CXX_FLAGS="${CXX_FLAGS}"

echo "==> Building..."
cmake --build build --config "${BUILD_TYPE}" --target itoa_benchmarks -j

echo "==> Running benchmark..."
./build/benchmarks/itoa_benchmarks
