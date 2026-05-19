// Batch contender — simditoa::to_chars_batch with auto variant selection
// (paper §5.6, Algorithm 1). One API call converts all N values; simditoa
// samples the input to pick heterogeneous vs homogeneous before the loop.
//
// All batch contenders write into per-element output buffers from the
// shared BatchArena so the I/O shape is identical across libraries.

#include "bench_data.hpp"
#include "simditoa.h"

#include <cstddef>

namespace {

void bench_simditoa_to_chars_batch(::benchmark::State &state) {
  const auto &values = ::bench::get_values_u64(
      static_cast<int>(state.range(0)), static_cast<int>(state.range(1)));
  auto &arena = ::bench::get_batch_arena(values.size());
  std::size_t bytes = 0;
  for (auto _ : state) {
    simditoa::to_chars_batch(values.data(), values.size(), arena.ptrs.data(),
                             arena.lengths.data());
    ::benchmark::DoNotOptimize(arena.storage.data());
    ::benchmark::ClobberMemory();
    std::size_t iter_bytes = 0;
    for (const auto L : arena.lengths) {
      iter_bytes += L;
    }
    bytes += iter_bytes;
  }
  ::bench::set_counters(state, bytes);
}

}  // namespace

BENCH_REGISTER_BATCH(bench_simditoa_to_chars_batch);
