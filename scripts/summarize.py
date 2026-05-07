#!/usr/bin/env python3
"""Summarize raw google/benchmark stdout into a Markdown RESULTS.md via OpenAI.

Usage:
    python summarize.py <input_raw.txt> <output.md>

Environment:
    OPENAI_API_KEY  required
    OPENAI_MODEL    optional, defaults to a current flagship chat model
    BENCH_MACHINE_TYPE  optional, included in the report header
    BENCH_VM_ZONE       optional, included in the report header
"""
from __future__ import annotations

import datetime as dt
import os
import sys
from pathlib import Path

from openai import OpenAI


SYSTEM_PROMPT = """You are a senior performance engineer. You will be given the
raw stdout from a google/benchmark run of a 64-bit-integer-to-string
benchmarking suite. Your job is to produce a concise, technically accurate
Markdown report.

Strict requirements:
- Do not invent numbers. Every figure in your output must appear in the raw
  input.
- Use ints/s as the primary throughput metric where available; fall back to
  ns/int otherwise.
- Numbers are formatted with thousands separators (e.g. 1,234,567).
- Identify the contenders (e.g. simditoa, std_to_chars, jeaiii_itoa, yy_itoa,
  rapidjson, fmtlib, null) and the workload distributions. Distribution codes
  in `state.range(0)` map as follows:
    dist:0 -> UNIFORM       (signed, full int64 range; mostly 18-19 digits)
    dist:1 -> LOG           (uniform over bit-widths [0, 63], random sign)
    dist:2 -> FIXED         (positive, exact decimal length in state.range(1))
    dist:3 -> UNIFORM_POS   (uniform over [0, INT64_MAX]; long, positive only)
    dist:4 -> LOG_HEAVY     (uniform over bit-widths [40, 63], positive; proxy
                             for timestamps, Snowflake IDs, monotonic counters)
- If the hardware metadata block at the top of the input indicates AVX-512
  IFMA/VBMI are absent, mention that simditoa runs its scalar fallback.

Workload framing for the report:
- The HEADLINE scoreboard reports the geometric mean of ints/s across the
  realistic-workload subset {UNIFORM_POS, LOG_HEAVY, FIXED:12, FIXED:16,
  FIXED:19}. Production int64 serialization (IDs, sizes, timestamps,
  counters) overwhelmingly lives in this regime, so this is the fair
  apples-to-apples ranking.
- Short-digit FIXED:{1,4,8} and signed UNIFORM are reported separately, NOT
  in the headline. Per the simditoa algorithm, its "small" (sub-10^8) kernel
  has a constant SIMD setup cost regardless of digit count, so scalar methods
  win at 1-8 digit outputs by design. Note this explicitly in the summary so
  readers understand the regression is structural, not a benchmark artifact.

Output structure (exactly this order, no extra preamble):
1. A short executive summary as 3 to 6 bullet points: headline winner by
   geomean ints/s on the realistic subset, fastest contender per workload
   family, notable outliers, and any hardware caveats.
2. **Headline scoreboard**: Markdown table ranked by geomean ints/s across
   {UNIFORM_POS, LOG_HEAVY, FIXED:12, FIXED:16, FIXED:19}. Columns:
   Contender, Geomean ints/s, UNIFORM_POS ints/s, LOG_HEAVY ints/s,
   FIXED:12 ints/s, FIXED:16 ints/s, FIXED:19 ints/s. Compute the geomean
   yourself from the raw numbers; show it with thousands separators.
3. **Short-digit appendix**: Markdown table for FIXED-length sweep
   (rows = contender, columns = FIXED:1, FIXED:4, FIXED:8, FIXED:12,
   FIXED:16, FIXED:19), ints/s. One sentence under it noting that simditoa's
   small-kernel cost is constant by algorithm design.
4. **Signed / mixed appendix**: Markdown table with UNIFORM ints/s and
   LOG ints/s per contender, for callers whose workload includes negatives
   or uniform-over-bit-widths.

Do not include the raw output, a heading, or a date line. The wrapper script
adds those itself.
"""


def main() -> int:
    if len(sys.argv) != 3:
        print(f"usage: {sys.argv[0]} <input_raw.txt> <output.md>", file=sys.stderr)
        return 2

    raw_path = Path(sys.argv[1])
    out_path = Path(sys.argv[2])

    raw = raw_path.read_text(encoding="utf-8", errors="replace")
    if not raw.strip():
        print("error: raw benchmark output is empty", file=sys.stderr)
        return 1

    api_key = os.environ.get("OPENAI_API_KEY")
    if not api_key:
        print("error: OPENAI_API_KEY is not set", file=sys.stderr)
        return 1

    model = os.environ.get("OPENAI_MODEL", "gpt-4.1")
    machine_type = os.environ.get("BENCH_MACHINE_TYPE", "c3-standard-8")
    vm_zone = os.environ.get("BENCH_VM_ZONE", "us-central1-a")

    client = OpenAI(api_key=api_key)

    user_msg = (
        "Raw google/benchmark output follows. Summarize it per the system "
        "prompt.\n\n```\n" + raw + "\n```\n"
    )

    print(f"==> Calling OpenAI model={model}", file=sys.stderr)
    resp = client.chat.completions.create(
        model=model,
        messages=[
            {"role": "system", "content": SYSTEM_PROMPT},
            {"role": "user", "content": user_msg},
        ],
        temperature=0.2,
    )
    summary = (resp.choices[0].message.content or "").strip()
    if not summary:
        print("error: OpenAI returned an empty summary", file=sys.stderr)
        return 1

    today = dt.date.today().isoformat()
    header = (
        f"# Benchmark results\n\n"
        f"_Generated {today} on a GCP `{machine_type}` VM in `{vm_zone}`._\n\n"
        f"_Summary produced by OpenAI `{model}`. Numbers are sourced from the raw "
        f"google/benchmark output included at the bottom of this file._\n\n"
    )

    raw_block = (
        "\n## Raw output\n\n"
        "<details>\n<summary>Click to expand raw <code>google/benchmark</code> "
        "stdout</summary>\n\n"
        "```\n" + raw.rstrip() + "\n```\n\n</details>\n"
    )

    out_path.write_text(header + summary.rstrip() + "\n" + raw_block, encoding="utf-8")
    print(f"==> Wrote {out_path}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
