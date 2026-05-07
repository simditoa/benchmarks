#include "bench_data.hpp"

#include <charconv>
#include <cstddef>

namespace {

void bench_std_to_chars(::benchmark::State &state) {
  const auto &values = ::bench::get_values(static_cast<int>(state.range(0)),
                                           static_cast<int>(state.range(1)));
  char buf[::bench::BUF_SIZE];
  std::size_t bytes = 0;
  for (auto _ : state) {
    std::size_t iter_bytes = 0;
    for (const auto &v : values) {
      auto res = std::to_chars(buf, buf + sizeof(buf), v);
      ::benchmark::DoNotOptimize(buf);
      iter_bytes += static_cast<std::size_t>(res.ptr - buf);
    }
    ::benchmark::ClobberMemory();
    bytes += iter_bytes;
  }
  ::bench::set_counters(state, bytes);
}

}  // namespace

BENCH_REGISTER_ALL(bench_std_to_chars);
