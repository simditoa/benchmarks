#include "bench_data.hpp"

#include <fmt/format.h>

#include <cstddef>

namespace {

void bench_fmtlib_fmt(::benchmark::State &state) {
  const auto &values = ::bench::get_values(static_cast<int>(state.range(0)),
                                           static_cast<int>(state.range(1)));
  std::size_t bytes = 0;
  for (auto _ : state) {
    std::size_t iter_bytes = 0;
    for (const auto &v : values) {
      fmt::format_int f(v);
      ::benchmark::DoNotOptimize(f.data());
      iter_bytes += f.size();
    }
    ::benchmark::ClobberMemory();
    bytes += iter_bytes;
  }
  ::bench::set_counters(state, bytes);
}

}  // namespace

BENCH_REGISTER_ALL(bench_fmtlib_fmt);
