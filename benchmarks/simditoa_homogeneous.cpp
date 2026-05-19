// Homogeneous variant of simditoa (paper §5.5): per-length dispatcher,
// unmasked direct stores. Same single-value loop as every other contender
// so the comparison stays apples-to-apples.

#include "bench_data.hpp"
#include "simditoa.h"

#include <cstddef>

namespace {

void bench_simditoa_to_chars_homogeneous(::benchmark::State &state) {
  const auto &values = ::bench::get_values(static_cast<int>(state.range(0)),
                                           static_cast<int>(state.range(1)));
  char buf[::bench::BUF_SIZE];
  std::size_t bytes = 0;
  for (auto _ : state) {
    std::size_t iter_bytes = 0;
    for (const auto &v : values) {
      iter_bytes += simditoa::to_chars_homogeneous(v, buf);
      ::benchmark::DoNotOptimize(buf);
    }
    ::benchmark::ClobberMemory();
    bytes += iter_bytes;
  }
  ::bench::set_counters(state, bytes);
}

}  // namespace

BENCH_REGISTER_ALL(bench_simditoa_to_chars_homogeneous);
