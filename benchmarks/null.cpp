// Baseline: loop overhead only. No conversion. Useful as a floor for the
// other contenders (everything must beat null on iteration cost alone).

#include "bench_data.hpp"

#include <cstddef>
#include <cstdint>

namespace {

void bench_null(::benchmark::State &state) {
  const auto &values = ::bench::get_values(static_cast<int>(state.range(0)),
                                           static_cast<int>(state.range(1)));
  std::size_t bytes = 0;
  for (auto _ : state) {
    for (const auto &v : values) {
      int64_t x = v;
      ::benchmark::DoNotOptimize(x);
    }
    ::benchmark::ClobberMemory();
    bytes += ::bench::NUM_VALUES * sizeof(int64_t);
  }
  ::bench::set_counters(state, bytes);
}

}  // namespace

BENCH_REGISTER_ALL(bench_null);
