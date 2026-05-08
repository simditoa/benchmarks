# Benchmarks

Benchmarks for 64-bit integer-to-string conversion implementations, built on top of [google/benchmark](https://github.com/google/benchmark).

## Latest results

See [RESULTS.md](./RESULTS.md) for the latest run on a GCP C3 (Sapphire Rapids, AVX-512 IFMA + VBMI) VM, summarized via the OpenAI API. Default machine type is `c3-standard-8`; trigger the workflow with a custom `machine_type` input to use a larger one.

To produce a fresh run, trigger the **Run benchmark on GCP** workflow under GitHub Actions. Required repository secrets: `GCP_SA_KEY` (service account JSON with Compute Admin), `GCP_PROJECT_ID`, `OPENAI_API_KEY`. See [`.github/workflows/benchmark.yml`](./.github/workflows/benchmark.yml) and [`terraform/`](./terraform/) for the full pipeline.

## Contenders

| Option                              | Implementation                                  |
| ----------------------------------- | ----------------------------------------------- |
| `BENCHMARK_BUILD_SIMDITOA`          | `simditoa::to_chars`                            |
| `BENCHMARK_BUILD_NULL`              | no-op baseline (loop overhead only)             |
| `BENCHMARK_BUILD_STD_TO_CHARS`      | `std::to_chars`                                 |
| `BENCHMARK_BUILD_YY_ITOA`           | `itoa_i64_yy` from ibireme/c_numconv_benchmark  |
| `BENCHMARK_BUILD_JEAIII_ITOA`       | `jeaiii::to_text_from_integer`                  |
| `BENCHMARK_BUILD_TENCENT_RAPIDJSON` | `rapidjson::internal::i64toa` (branchlut)       |
| `BENCHMARK_BUILD_FMTLIB_FMT`        | `fmt::format_int`                               |

Every contender is enabled by default. Disable any with `-DBENCHMARK_BUILD_<NAME>=OFF`.

## Build and run

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target itoa_benchmarks -j
./build/benchmarks/itoa_benchmarks
```

## Workloads

Each contender runs against the same set of int64 inputs, generated once and cached:

- `dist=UNIFORM` - uniform across the full int64 range; nearly all values land at 18-19 digits.
- `dist=UNIFORM_POS` - uniform over `[0, INT64_MAX]`; same length profile, no sign-mispredict tax.
- `dist=LOG` - uniform over bit-widths `[0, 63]` then random sign; equal weight on each digit length.
- `dist=LOG_HEAVY` - uniform over bit-widths `[40, 63]`, positive only; realistic proxy for timestamps, Snowflake IDs, monotonic counters.
- `dist=FIXED, len=N` - positive values with exactly `N` decimal digits, swept across `1, 4, 8, 12, 16, 19`.

Reported counters: `ints/s`, `bytes/s`, `ns/int`. Each configuration is repeated 10 times; only the max-throughput aggregate is shown.

The headline scoreboard in `RESULTS.md` is the geometric mean of `ints/s` across the realistic subset `{UNIFORM_POS, LOG_HEAVY, FIXED:12, FIXED:16, FIXED:19}`. Short-digit FIXED `{1, 4, 8}` and signed UNIFORM are reported separately. simditoa's small-value kernel (inputs `< 10^8`) pays a constant SIMD setup cost regardless of digit count, so scalar methods are faster at 1-8 digit outputs by algorithm design; that regression is real but is not where production int64 serialization lives.

## AVX-512 builds (simditoa)

`simditoa`'s AVX-512 IFMA + VBMI code path is gated on compile flags. To enable it:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_FLAGS="-mavx512f -mavx512dq -mavx512bw -mavx512vl -mavx512ifma -mavx512vbmi"
```

Or use `script.sh` which probes `/proc/cpuinfo` and configures the build automatically (Linux only).

## Adding a contender

1. Create `benchmarks/<name>.cpp`. Include `bench_data.hpp`, write one `bench_<name>` function, and register it with the sweep macros.
2. Add a `BENCHMARK_BUILD_<NAME>` option to the root `CMakeLists.txt`.
3. Add a guarded block to `benchmarks/CMakeLists.txt` that fetches any required deps and appends the source via `target_sources(itoa_benchmarks PRIVATE <name>.cpp)` plus `target_link_libraries`.
