#pragma once

#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <map>
#include <random>
#include <utility>
#include <vector>

namespace bench {

constexpr std::size_t NUM_VALUES = 1'000'000;

// Buffer must hold sign + up to 19 digits + NUL. 32 leaves slack for any
// contender that wants to align/zero-init.
constexpr std::size_t BUF_SIZE = 32;

// Distribution selectors passed via state.range(0).
//   D_UNIFORM     : full int64 range, uniform. ~all values land in 18-19 digits.
//   D_LOG         : uniform over bit-widths [0, 63] then random sign. Equal
//                   weight on each digit length.
//   D_FIXED       : positive values with exactly state.range(1) decimal digits.
//   D_UNIFORM_POS : uniform over [0, INT64_MAX]. Removes the sign-mispredict
//                   tax from the wide-range workload. Defensible because most
//                   production int64 serialization (IDs, sizes, timestamps) is
//                   non-negative.
//   D_LOG_HEAVY   : uniform over bit-widths [40, 63], positive only. Realistic
//                   proxy for timestamps, Snowflake IDs, monotonic counters.
enum Dist : int {
  D_UNIFORM = 0,
  D_LOG = 1,
  D_FIXED = 2,
  D_UNIFORM_POS = 3,
  D_LOG_HEAVY = 4,
};

inline std::vector<int64_t> make_uniform() {
  std::mt19937_64 rng(42);
  std::uniform_int_distribution<int64_t> dist(INT64_MIN, INT64_MAX);
  std::vector<int64_t> v(NUM_VALUES);
  for (auto &x : v) {
    x = dist(rng);
  }
  return v;
}

inline std::vector<int64_t> make_log_uniform() {
  std::mt19937_64 rng(43);
  std::uniform_int_distribution<int> bits_dist(0, 63);
  std::vector<int64_t> v(NUM_VALUES);
  for (auto &x : v) {
    int b = bits_dist(rng);
    uint64_t mask = (b == 0) ? 0ULL : (~0ULL >> (64 - b));
    uint64_t mag = static_cast<uint64_t>(rng()) & mask;
    bool neg = (rng() & 1ULL) != 0;
    x = neg ? -static_cast<int64_t>(mag) : static_cast<int64_t>(mag);
  }
  return v;
}

inline std::vector<int64_t> make_uniform_positive() {
  std::mt19937_64 rng(45);
  std::uniform_int_distribution<int64_t> dist(0, INT64_MAX);
  std::vector<int64_t> v(NUM_VALUES);
  for (auto &x : v) {
    x = dist(rng);
  }
  return v;
}

inline std::vector<int64_t> make_log_heavy() {
  std::mt19937_64 rng(46);
  std::uniform_int_distribution<int> bits_dist(40, 63);
  std::vector<int64_t> v(NUM_VALUES);
  for (auto &x : v) {
    int b = bits_dist(rng);
    uint64_t mask = (~0ULL >> (64 - b));
    uint64_t mag = static_cast<uint64_t>(rng()) & mask;
    x = static_cast<int64_t>(mag);
  }
  return v;
}

inline std::vector<int64_t> make_fixed_length(int len) {
  std::mt19937_64 rng(static_cast<uint64_t>(44 + len));
  uint64_t pow10_lo = 1;
  for (int i = 1; i < len; ++i) {
    pow10_lo *= 10;
  }
  uint64_t lo = (len == 1) ? 0ULL : pow10_lo;
  uint64_t hi;
  if (len >= 19) {
    hi = static_cast<uint64_t>(INT64_MAX);
  } else {
    hi = pow10_lo * 10 - 1;
  }
  std::uniform_int_distribution<uint64_t> dist(lo, hi);
  std::vector<int64_t> v(NUM_VALUES);
  for (auto &x : v) {
    x = static_cast<int64_t>(dist(rng));
  }
  return v;
}

inline const std::vector<int64_t> &get_values(int dist, int param) {
  static std::map<std::pair<int, int>, std::vector<int64_t>> cache;
  auto key = std::make_pair(dist, param);
  auto it = cache.find(key);
  if (it != cache.end()) {
    return it->second;
  }
  std::vector<int64_t> v;
  switch (dist) {
  case D_UNIFORM:
    v = make_uniform();
    break;
  case D_LOG:
    v = make_log_uniform();
    break;
  case D_FIXED:
    v = make_fixed_length(param);
    break;
  case D_UNIFORM_POS:
    v = make_uniform_positive();
    break;
  case D_LOG_HEAVY:
    v = make_log_heavy();
    break;
  }
  return cache.emplace(key, std::move(v)).first->second;
}

// ---- Batch helpers ----
//
// The batch sweep gives every contender the same I/O shape: N input values
// converted into N per-element output buffers. simditoa drives this with its
// to_chars_batch API; the others loop their single-value function. The
// per-element output cost is paid by all contenders so the comparison stays
// apples-to-apples. Only the conversion logic differs.
//
// uint64_t-cast view of get_values(). simditoa::to_chars_batch is uint64-only,
// so the batch sweep uses the positive-only distributions (see
// BENCH_REGISTER_BATCH below) where this cast is a no-op semantically.
inline const std::vector<uint64_t> &get_values_u64(int dist, int param) {
  static std::map<std::pair<int, int>, std::vector<uint64_t>> cache;
  auto key = std::make_pair(dist, param);
  auto it = cache.find(key);
  if (it != cache.end()) {
    return it->second;
  }
  const auto &signed_values = get_values(dist, param);
  std::vector<uint64_t> v(signed_values.size());
  for (std::size_t i = 0; i < signed_values.size(); ++i) {
    v[i] = static_cast<uint64_t>(signed_values[i]);
  }
  return cache.emplace(key, std::move(v)).first->second;
}

struct BatchArena {
  std::vector<char> storage;
  std::vector<char *> ptrs;
  std::vector<std::size_t> lengths;
};

inline BatchArena &get_batch_arena(std::size_t count) {
  static BatchArena a;
  if (a.ptrs.size() != count) {
    a.storage.assign(count * BUF_SIZE, 0);
    a.ptrs.resize(count);
    a.lengths.assign(count, 0);
    for (std::size_t i = 0; i < count; ++i) {
      a.ptrs[i] = a.storage.data() + i * BUF_SIZE;
    }
  }
  return a;
}

inline void set_counters(::benchmark::State &state, std::size_t bytes) {
  state.counters["ints/s"] = ::benchmark::Counter(
      static_cast<double>(NUM_VALUES),
      ::benchmark::Counter::kIsIterationInvariantRate);
  state.counters["bytes/s"] = ::benchmark::Counter(
      static_cast<double>(bytes), ::benchmark::Counter::kIsRate,
      ::benchmark::Counter::OneK::kIs1000);
  state.counters["ns/int"] = ::benchmark::Counter(
      static_cast<double>(NUM_VALUES),
      ::benchmark::Counter::kIsIterationInvariantRate |
          ::benchmark::Counter::kInvert);
}

inline auto max_stat = [](const std::vector<double> &v) {
  return *std::max_element(v.begin(), v.end());
};

}  // namespace bench

// Register every contender against UNIFORM, LOG, and the full FIXED length
// sweep (1/4/8/12/16/19). 10 reps, max-throughput aggregate.
#define BENCH_REGISTER_ALL(fn)                                          \
  BENCHMARK(fn)                                                         \
      ->ArgNames({"dist", "param"})                                     \
      ->Args({::bench::D_UNIFORM, 0})                                   \
      ->Args({::bench::D_UNIFORM_POS, 0})                               \
      ->Args({::bench::D_LOG, 0})                                       \
      ->Args({::bench::D_LOG_HEAVY, 0})                                 \
      ->Args({::bench::D_FIXED, 1})                                     \
      ->Args({::bench::D_FIXED, 4})                                     \
      ->Args({::bench::D_FIXED, 8})                                     \
      ->Args({::bench::D_FIXED, 12})                                    \
      ->Args({::bench::D_FIXED, 16})                                    \
      ->Args({::bench::D_FIXED, 19})                                    \
      ->Repetitions(10)                                                 \
      ->ComputeStatistics("max", ::bench::max_stat)                     \
      ->DisplayAggregatesOnly(true)

// Batch sweep — positive-only distributions, since the batch API is uint64-only.
// Same length-coverage shape as BENCH_REGISTER_ALL minus the signed cases.
#define BENCH_REGISTER_BATCH(fn)                                        \
  BENCHMARK(fn)                                                         \
      ->ArgNames({"dist", "param"})                                     \
      ->Args({::bench::D_UNIFORM_POS, 0})                               \
      ->Args({::bench::D_LOG_HEAVY, 0})                                 \
      ->Args({::bench::D_FIXED, 1})                                     \
      ->Args({::bench::D_FIXED, 4})                                     \
      ->Args({::bench::D_FIXED, 8})                                     \
      ->Args({::bench::D_FIXED, 12})                                    \
      ->Args({::bench::D_FIXED, 16})                                    \
      ->Args({::bench::D_FIXED, 19})                                    \
      ->Repetitions(10)                                                 \
      ->ComputeStatistics("max", ::bench::max_stat)                     \
      ->DisplayAggregatesOnly(true)
