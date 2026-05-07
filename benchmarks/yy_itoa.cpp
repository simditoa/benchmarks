#include "bench_data.hpp"

#include <cstddef>
#include <cstdint>

extern "C" char *itoa_i64_yy(int64_t val, char *buf);

namespace {

void bench_yy_itoa(::benchmark::State &state) {
  const auto &values = ::bench::get_values(static_cast<int>(state.range(0)),
                                           static_cast<int>(state.range(1)));
  char buf[::bench::BUF_SIZE];
  std::size_t bytes = 0;
  for (auto _ : state) {
    std::size_t iter_bytes = 0;
    for (const auto &v : values) {
      char *end = itoa_i64_yy(v, buf);
      ::benchmark::DoNotOptimize(buf);
      iter_bytes += static_cast<std::size_t>(end - buf);
    }
    ::benchmark::ClobberMemory();
    bytes += iter_bytes;
  }
  ::bench::set_counters(state, bytes);
}

}  // namespace

BENCH_REGISTER_ALL(bench_yy_itoa);
