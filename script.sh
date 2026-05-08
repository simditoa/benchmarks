#!/usr/bin/env bash
set -euo pipefail

# Curl-pipe-bash bootstrap for the itoa benchmarks suite. Clones the repo to
# WORKDIR (or updates an existing clone), then delegates the build-and-run to
# scripts/build-and-run.sh.
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

echo "==> Ensuring git is available..."
"${SUDO[@]}" apt-get update -y >/dev/null
"${SUDO[@]}" apt-get install -y --no-install-recommends ca-certificates git >/dev/null

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
EMIT_METADATA="${EMIT_METADATA:-0}" exec bash scripts/build-and-run.sh
