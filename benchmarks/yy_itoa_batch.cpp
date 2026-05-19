// Batch counterpart for itoa_i64_yy.

#include "bench_data.hpp"

#include <cstddef>
#include <cstdint>

extern "C" char *itoa_u64_yy(uint64_t val, char *buf);

namespace {

void bench_yy_itoa_batch(::benchmark::State &state) {
  const auto &values = ::bench::get_values_u64(
      static_cast<int>(state.range(0)), static_cast<int>(state.range(1)));
  auto &arena = ::bench::get_batch_arena(values.size());
  std::size_t bytes = 0;
  for (auto _ : state) {
    std::size_t iter_bytes = 0;
    for (std::size_t i = 0; i < values.size(); ++i) {
      char *buf = arena.ptrs[i];
      char *end = itoa_u64_yy(values[i], buf);
      iter_bytes += static_cast<std::size_t>(end - buf);
    }
    ::benchmark::DoNotOptimize(arena.storage.data());
    ::benchmark::ClobberMemory();
    bytes += iter_bytes;
  }
  ::bench::set_counters(state, bytes);
}

}  // namespace

BENCH_REGISTER_BATCH(bench_yy_itoa_batch);
