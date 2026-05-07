// Foundation contender file. Every other contender mirrors this template:
//   1. include bench_data.hpp + the contender's header
//   2. write one bench_<name>(State&) function
//   3. call BENCH_REGISTER_ALL(bench_<name>)

#include "bench_data.hpp"
#include "simditoa.h"

#include <cstddef>

namespace {

void bench_simditoa_to_chars(::benchmark::State &state) {
  const auto &values = ::bench::get_values(static_cast<int>(state.range(0)),
                                           static_cast<int>(state.range(1)));
  char buf[::bench::BUF_SIZE];
  std::size_t bytes = 0;
  for (auto _ : state) {
    std::size_t iter_bytes = 0;
    for (const auto &v : values) {
      iter_bytes += simditoa::to_chars(v, buf);
      ::benchmark::DoNotOptimize(buf);
    }
    ::benchmark::ClobberMemory();
    bytes += iter_bytes;
  }
  ::bench::set_counters(state, bytes);
}

}  // namespace

BENCH_REGISTER_ALL(bench_simditoa_to_chars);
