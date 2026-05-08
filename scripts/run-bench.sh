#!/usr/bin/env bash
set -euo pipefail

# Remote-side benchmark runner. Expects the repo to already be present in the
# current working directory (e.g. scp'd from a GitHub Actions runner).
# Delegates to scripts/build-and-run.sh, which builds the suite and prints the
# google/benchmark output to stdout for the caller to capture.

exec bash "$(dirname "$0")/build-and-run.sh"
