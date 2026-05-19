// Batch counterpart for fmt::format_int.

#include "bench_data.hpp"

#include <fmt/format.h>

#include <cstddef>
#include <cstring>

namespace {

void bench_fmtlib_fmt_batch(::benchmark::State &state) {
  const auto &values = ::bench::get_values_u64(
      static_cast<int>(state.range(0)), static_cast<int>(state.range(1)));
  auto &arena = ::bench::get_batch_arena(values.size());
  std::size_t bytes = 0;
  for (auto _ : state) {
    std::size_t iter_bytes = 0;
    for (std::size_t i = 0; i < values.size(); ++i) {
      fmt::format_int f(values[i]);
      std::memcpy(arena.ptrs[i], f.data(), f.size());
      iter_bytes += f.size();
    }
    ::benchmark::DoNotOptimize(arena.storage.data());
    ::benchmark::ClobberMemory();
    bytes += iter_bytes;
  }
  ::bench::set_counters(state, bytes);
}

}  // namespace

BENCH_REGISTER_BATCH(bench_fmtlib_fmt_batch);
