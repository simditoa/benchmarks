#!/usr/bin/env bash
set -euo pipefail

# Remote-side benchmark runner. Expects the repo to already be present in the
# current working directory (e.g. scp'd from a GitHub Actions runner). Builds
# and runs the itoa benchmark suite, printing the google/benchmark output to
# stdout for the caller to capture.
#
# Optional environment overrides:
#   BUILD_TYPE=Release
#   EXTRA_CXX_FLAGS=""    # overrides auto-detected -march flags
#   FORCE_AVX512=0        # set to 1 to force AVX-512 flags even if cpuinfo lookup fails

BUILD_TYPE="${BUILD_TYPE:-Release}"
EXTRA_CXX_FLAGS="${EXTRA_CXX_FLAGS:-}"
FORCE_AVX512="${FORCE_AVX512:-0}"

if [[ "${EUID}" -eq 0 ]]; then
  SUDO=()
else
  SUDO=(sudo)
fi

echo "==> Installing build dependencies..." >&2
"${SUDO[@]}" apt-get update -y >&2
"${SUDO[@]}" DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
  ca-certificates \
  build-essential \
  cmake \
  git >&2

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
    echo "==> Detected AVX-512 IFMA + VBMI: enabling AVX-512 build (${AUTO_FLAGS})" >&2
  else
    echo "==> AVX-512 IFMA + VBMI not detected: building scalar fallback only" >&2
  fi
else
  echo "==> Using user-provided EXTRA_CXX_FLAGS=${EXTRA_CXX_FLAGS}" >&2
fi

CXX_FLAGS="${EXTRA_CXX_FLAGS:-${AUTO_FLAGS}}"

echo "==> Configuring (BUILD_TYPE=${BUILD_TYPE}, CXX_FLAGS='${CXX_FLAGS}')..." >&2
rm -rf build
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
  -DCMAKE_CXX_FLAGS="${CXX_FLAGS}" >&2

echo "==> Building..." >&2
cmake --build build --config "${BUILD_TYPE}" --target itoa_benchmarks -j >&2

echo "==> Hardware metadata --------------------------------------------------"
echo "machine_type: ${BENCH_MACHINE_TYPE:-unknown}"
echo "cpu_model: $(grep -m1 'model name' /proc/cpuinfo | sed 's/^[^:]*: //')"
echo "cpu_cores: $(nproc)"
echo "kernel: $(uname -r)"
echo "avx512_ifma: ${HAS_AVX512_IFMA}"
echo "avx512_vbmi: ${HAS_AVX512_VBMI}"
echo "cxx_flags: ${CXX_FLAGS}"
echo "------------------------------------------------------------------------"

echo "==> Running benchmark..." >&2
./build/benchmarks/itoa_benchmarks --benchmark_format=console
