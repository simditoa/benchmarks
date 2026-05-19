// Batch counterpart for std::to_chars. Same per-element output buffer
// pattern as simditoa_batch.cpp; the conversion logic is the only thing
// that differs across batch contenders.

#include "bench_data.hpp"

#include <charconv>
#include <cstddef>

namespace {

void bench_std_to_chars_batch(::benchmark::State &state) {
  const auto &values = ::bench::get_values_u64(
      static_cast<int>(state.range(0)), static_cast<int>(state.range(1)));
  auto &arena = ::bench::get_batch_arena(values.size());
  std::size_t bytes = 0;
  for (auto _ : state) {
    std::size_t iter_bytes = 0;
    for (std::size_t i = 0; i < values.size(); ++i) {
      char *buf = arena.ptrs[i];
      auto res = std::to_chars(buf, buf + ::bench::BUF_SIZE, values[i]);
      iter_bytes += static_cast<std::size_t>(res.ptr - buf);
    }
    ::benchmark::DoNotOptimize(arena.storage.data());
    ::benchmark::ClobberMemory();
    bytes += iter_bytes;
  }
  ::bench::set_counters(state, bytes);
}

}  // namespace

BENCH_REGISTER_BATCH(bench_std_to_chars_batch);
