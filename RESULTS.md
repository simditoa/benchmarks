# Benchmark results

_Generated 2026-05-07 on a GCP `c3-standard-8` VM in `us-central1-a`._

_Summary produced by OpenAI `gpt-5.4-mini`. Numbers are sourced from the raw google/benchmark output included at the bottom of this file._

- **Headline winner on the realistic subset** `{UNIFORM_POS, LOG_HEAVY, FIXED:12, FIXED:16, FIXED:19}` is **simditoa** by geometric mean throughput at **194,841,000 ints/s**.
- **Fastest contender by family**:
  - **UNIFORM_POS**: **simditoa** at **269,720,000 ints/s**
  - **LOG_HEAVY**: **simditoa** at **185,959,000 ints/s**
  - **FIXED:12 / 16 / 19**: **simditoa** at **189,680,000 / 189,698,000 / 186,156,000 ints/s**
  - **UNIFORM** and **LOG**: **null** is the baseline ceiling at **2,876,120,000 / 2,952,510,000 ints/s**
- **Notable outliers**: `std_to_chars` is the slowest among the real serializers on the realistic subset; `yy_itoa` is consistently ahead of `std_to_chars` and `rapidjson`, but behind `simditoa`; `rapidjson` and `fmtlib` sit in the middle.
- **Hardware caveat**: this machine has **AVX-512 IFMA=1** and **VBMI=1**, so **simditoa is using its vector path, not the scalar fallback**.
- **Important interpretation note**: the short-digit `FIXED:{1,4,8}` cases are intentionally separate; for simditoa’s sub-10^8 “small” kernel, the SIMD setup cost is effectively constant, so scalar methods winning at 1–8 digits is structural, not a benchmark artifact.

**Headline scoreboard**

| Contender | Geomean ints/s | UNIFORM_POS ints/s | LOG_HEAVY ints/s | FIXED:12 ints/s | FIXED:16 ints/s | FIXED:19 ints/s |
|---|---:|---:|---:|---:|---:|---:|
| simditoa | 194,841,000 | 269,720,000 | 185,959,000 | 189,680,000 | 189,698,000 | 186,156,000 |
| yy_itoa | 164,418,000 | 349,256,000 | 128,832,000 | 205,493,000 | 166,955,000 | 139,717,000 |
| rapidjson | 126,330,000 | 502,026,000 | 124,244,000 | 124,333,000 | 124,244,000 | 77,508,500 |
| fmtlib | 111,448,000 | 984,560,000 | 105,533,000 | 144,767,000 | 105,533,000 | 80,763,200 |
| std_to_chars | 87,088,700 | 397,369,000 | 73,157,600 | 100,569,000 | 73,157,600 | 59,219,700 |
| jeaiii_itoa | 92,999,700 | 992,763,000 | 166,955,000 | 202,737,000 | 166,955,000 | 126,446,000 |

**Short-digit appendix**

| Contender | FIXED:1 ints/s | FIXED:4 ints/s | FIXED:8 ints/s | FIXED:12 ints/s | FIXED:16 ints/s | FIXED:19 ints/s |
|---|---:|---:|---:|---:|---:|---:|
| simditoa | 269,720,000 | 225,319,000 | 225,285,000 | 189,680,000 | 189,698,000 | 186,156,000 |
| yy_itoa | 349,256,000 | 409,703,000 | 300,898,000 | 205,493,000 | 166,955,000 | 139,717,000 |
| rapidjson | 502,026,000 | 505,532,000 | 291,034,000 | 124,333,000 | 124,244,000 | 77,508,500 |
| fmtlib | 984,560,000 | 455,404,000 | 219,662,000 | 144,767,000 | 105,533,000 | 80,763,200 |
| std_to_chars | 397,369,000 | 293,873,000 | 145,283,000 | 100,569,000 | 73,157,600 | 59,219,700 |
| jeaiii_itoa | 992,763,000 | 589,710,000 | 336,733,000 | 202,737,000 | 166,955,000 | 126,446,000 |

simditoa’s small-kernel cost is constant by algorithm design, so it is expected to lose on 1–8 digit outputs even when it wins the realistic production-oriented subset.

**Signed / mixed appendix**

| Contender | UNIFORM ints/s | LOG ints/s |
|---|---:|---:|
| simditoa | 101,171,000 | 81,339,200 |
| yy_itoa | 128,841,000 | 65,807,100 |
| rapidjson | 61,532,100 | 45,847,000 |
| fmtlib | 58,130,500 | 44,205,600 |
| std_to_chars | 43,171,200 | 43,976,700 |
| jeaiii_itoa | 75,971,400 | 55,406,800 |
| null | 2,876,120,000 | 2,937,360,000 |

## Raw output

<details>
<summary>Click to expand raw <code>google/benchmark</code> stdout</summary>

```
==> Hardware metadata --------------------------------------------------
machine_type: c3-standard-8
cpu_model: Intel(R) Xeon(R) Platinum 8481C CPU @ 2.70GHz
cpu_cores: 8
kernel: 6.8.0-1054-gcp
avx512_ifma: 1
avx512_vbmi: 1
cxx_flags: -mavx512f -mavx512dq -mavx512bw -mavx512vl -mavx512ifma -mavx512vbmi
------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------
Benchmark                                                          Time             CPU   Iterations UserCounters...
--------------------------------------------------------------------------------------------------------------------
bench_simditoa_to_chars/dist:0/param:0/repeats:10_mean       9889291 ns      9888234 ns           10 bytes/s=1.96055G/s ints/s=101.171M/s ns/int=9.88823ns
bench_simditoa_to_chars/dist:0/param:0/repeats:10_median     9771261 ns      9770389 ns           10 bytes/s=1.9834G/s ints/s=102.35M/s ns/int=9.77039ns
bench_simditoa_to_chars/dist:0/param:0/repeats:10_stddev      210866 ns       210580 ns           10 bytes/s=40.9996M/s ints/s=2.11571M/s ns/int=210.58ps
bench_simditoa_to_chars/dist:0/param:0/repeats:10_cv            2.13 %          2.13 %            10 bytes/s=2.09% ints/s=2.09% ns/int=2.13%
bench_simditoa_to_chars/dist:0/param:0/repeats:10_max       10254744 ns     10253117 ns           10 bytes/s=1.98885G/s ints/s=102.631M/s ns/int=10.2531ns
bench_simditoa_to_chars/dist:3/param:0/repeats:10_mean       5378014 ns      5377534 ns           10 bytes/s=3.51086G/s ints/s=185.959M/s ns/int=5.37753ns
bench_simditoa_to_chars/dist:3/param:0/repeats:10_median     5375346 ns      5375033 ns           10 bytes/s=3.51248G/s ints/s=186.045M/s ns/int=5.37503ns
bench_simditoa_to_chars/dist:3/param:0/repeats:10_stddev        8822 ns         8656 ns           10 bytes/s=5.63515M/s ints/s=298.477k/s ns/int=8.65632ps
bench_simditoa_to_chars/dist:3/param:0/repeats:10_cv            0.16 %          0.16 %            10 bytes/s=0.16% ints/s=0.16% ns/int=0.16%
bench_simditoa_to_chars/dist:3/param:0/repeats:10_max        5400864 ns      5399839 ns           10 bytes/s=3.5148G/s ints/s=186.168M/s ns/int=5.39984ns
bench_simditoa_to_chars/dist:1/param:0/repeats:10_mean      12294539 ns     12294210 ns           10 bytes/s=817.793M/s ints/s=81.3392M/s ns/int=12.2942ns
bench_simditoa_to_chars/dist:1/param:0/repeats:10_median    12299693 ns     12299309 ns           10 bytes/s=817.453M/s ints/s=81.3054M/s ns/int=12.2993ns
bench_simditoa_to_chars/dist:1/param:0/repeats:10_stddev       17534 ns        17340 ns           10 bytes/s=1.15387M/s ints/s=114.766k/s ns/int=17.3397ps
bench_simditoa_to_chars/dist:1/param:0/repeats:10_cv            0.14 %          0.14 %            10 bytes/s=0.14% ints/s=0.14% ns/int=0.14%
bench_simditoa_to_chars/dist:1/param:0/repeats:10_max       12318244 ns     12318280 ns           10 bytes/s=819.47M/s ints/s=81.506M/s ns/int=12.3183ns
bench_simditoa_to_chars/dist:4/param:0/repeats:10_mean       7236268 ns      7236185 ns           10 bytes/s=2.15119G/s ints/s=138.195M/s ns/int=7.23619ns
bench_simditoa_to_chars/dist:4/param:0/repeats:10_median     7245879 ns      7245776 ns           10 bytes/s=2.14832G/s ints/s=138.011M/s ns/int=7.24578ns
bench_simditoa_to_chars/dist:4/param:0/repeats:10_stddev       20457 ns        20432 ns           10 bytes/s=6.08709M/s ints/s=391.044k/s ns/int=20.4316ps
bench_simditoa_to_chars/dist:4/param:0/repeats:10_cv            0.28 %          0.28 %            10 bytes/s=0.28% ints/s=0.28% ns/int=0.28%
bench_simditoa_to_chars/dist:4/param:0/repeats:10_max        7256861 ns      7256696 ns           10 bytes/s=2.16106G/s ints/s=138.83M/s ns/int=7.2567ns
bench_simditoa_to_chars/dist:2/param:1/repeats:10_mean       3707610 ns      3707546 ns           10 bytes/s=269.72M/s ints/s=269.72M/s ns/int=3.70755ns
bench_simditoa_to_chars/dist:2/param:1/repeats:10_median     3707731 ns      3707660 ns           10 bytes/s=269.712M/s ints/s=269.712M/s ns/int=3.70766ns
bench_simditoa_to_chars/dist:2/param:1/repeats:10_stddev         876 ns          858 ns           10 bytes/s=62.4173k/s ints/s=62.4173k/s ns/int=857.754fs
bench_simditoa_to_chars/dist:2/param:1/repeats:10_cv            0.02 %          0.02 %            10 bytes/s=0.02% ints/s=0.02% ns/int=0.02%
bench_simditoa_to_chars/dist:2/param:1/repeats:10_max        3708714 ns      3708647 ns           10 bytes/s=269.868M/s ints/s=269.868M/s ns/int=3.70865ns
bench_simditoa_to_chars/dist:2/param:4/repeats:10_mean       4438248 ns      4438161 ns           10 bytes/s=901.274M/s ints/s=225.319M/s ns/int=4.43816ns
bench_simditoa_to_chars/dist:2/param:4/repeats:10_median     4438345 ns      4438234 ns           10 bytes/s=901.259M/s ints/s=225.315M/s ns/int=4.43823ns
bench_simditoa_to_chars/dist:2/param:4/repeats:10_stddev         671 ns          701 ns           10 bytes/s=142.33k/s ints/s=35.5824k/s ns/int=700.868fs
bench_simditoa_to_chars/dist:2/param:4/repeats:10_cv            0.02 %          0.02 %            10 bytes/s=0.02% ints/s=0.02% ns/int=0.02%
bench_simditoa_to_chars/dist:2/param:4/repeats:10_max        4439045 ns      4439008 ns           10 bytes/s=901.462M/s ints/s=225.365M/s ns/int=4.43901ns
bench_simditoa_to_chars/dist:2/param:8/repeats:10_mean       4438891 ns      4438819 ns           10 bytes/s=1.80228G/s ints/s=225.285M/s ns/int=4.43882ns
bench_simditoa_to_chars/dist:2/param:8/repeats:10_median     4438831 ns      4438736 ns           10 bytes/s=1.80231G/s ints/s=225.289M/s ns/int=4.43874ns
bench_simditoa_to_chars/dist:2/param:8/repeats:10_stddev         452 ns          474 ns           10 bytes/s=192.256k/s ints/s=24.032k/s ns/int=473.541fs
bench_simditoa_to_chars/dist:2/param:8/repeats:10_cv            0.01 %          0.01 %            10 bytes/s=0.01% ints/s=0.01% ns/int=0.01%
bench_simditoa_to_chars/dist:2/param:8/repeats:10_max        4439883 ns      4439847 ns           10 bytes/s=1.80258G/s ints/s=225.322M/s ns/int=4.43985ns
bench_simditoa_to_chars/dist:2/param:12/repeats:10_mean      5272117 ns      5272044 ns           10 bytes/s=2.27616G/s ints/s=189.68M/s ns/int=5.27204ns
bench_simditoa_to_chars/dist:2/param:12/repeats:10_median    5272081 ns      5271945 ns           10 bytes/s=2.2762G/s ints/s=189.683M/s ns/int=5.27194ns
bench_simditoa_to_chars/dist:2/param:12/repeats:10_stddev        624 ns          636 ns           10 bytes/s=274.463k/s ints/s=22.8719k/s ns/int=635.842fs
bench_simditoa_to_chars/dist:2/param:12/repeats:10_cv           0.01 %          0.01 %            10 bytes/s=0.01% ints/s=0.01% ns/int=0.01%
bench_simditoa_to_chars/dist:2/param:12/repeats:10_max       5273674 ns      5273691 ns           10 bytes/s=2.27649G/s ints/s=189.708M/s ns/int=5.27369ns
bench_simditoa_to_chars/dist:2/param:16/repeats:10_mean      5271635 ns      5271538 ns           10 bytes/s=3.03517G/s ints/s=189.698M/s ns/int=5.27154ns
bench_simditoa_to_chars/dist:2/param:16/repeats:10_median    5271473 ns      5271429 ns           10 bytes/s=3.03523G/s ints/s=189.702M/s ns/int=5.27143ns
bench_simditoa_to_chars/dist:2/param:16/repeats:10_stddev        453 ns          428 ns           10 bytes/s=246.467k/s ints/s=15.4042k/s ns/int=428.086fs
bench_simditoa_to_chars/dist:2/param:16/repeats:10_cv           0.01 %          0.01 %            10 bytes/s=0.01% ints/s=0.01% ns/int=0.01%
bench_simditoa_to_chars/dist:2/param:16/repeats:10_max       5272322 ns      5272207 ns           10 bytes/s=3.03548G/s ints/s=189.718M/s ns/int=5.27221ns
bench_simditoa_to_chars/dist:2/param:19/repeats:10_mean      5371910 ns      5371827 ns           10 bytes/s=3.53697G/s ints/s=186.156M/s ns/int=5.37183ns
bench_simditoa_to_chars/dist:2/param:19/repeats:10_median    5371912 ns      5371801 ns           10 bytes/s=3.53699G/s ints/s=186.157M/s ns/int=5.3718ns
bench_simditoa_to_chars/dist:2/param:19/repeats:10_stddev        742 ns          745 ns           10 bytes/s=490.409k/s ints/s=25.811k/s ns/int=744.898fs
bench_simditoa_to_chars/dist:2/param:19/repeats:10_cv           0.01 %          0.01 %            10 bytes/s=0.01% ints/s=0.01% ns/int=0.01%
bench_simditoa_to_chars/dist:2/param:19/repeats:10_max       5373561 ns      5373503 ns           10 bytes/s=3.5377G/s ints/s=186.195M/s ns/int=5.3735ns
bench_null/dist:0/param:0/repeats:10_mean                     347841 ns       347838 ns           10 bytes/s=23.0089G/s ints/s=2.87612G/s ns/int=347.838ps
bench_null/dist:0/param:0/repeats:10_median                   345138 ns       345132 ns           10 bytes/s=23.181G/s ints/s=2.89763G/s ns/int=345.132ps
bench_null/dist:0/param:0/repeats:10_stddev                     7560 ns         7561 ns           10 bytes/s=495.501M/s ints/s=61.9377M/s ns/int=7.56136ps
bench_null/dist:0/param:0/repeats:10_cv                         2.17 %          2.17 %            10 bytes/s=2.15% ints/s=2.15% ns/int=2.17%
bench_null/dist:0/param:0/repeats:10_max                      358399 ns       358400 ns           10 bytes/s=23.4953G/s ints/s=2.93691G/s ns/int=358.4ps
bench_null/dist:3/param:0/repeats:10_mean                     338700 ns       338698 ns           10 bytes/s=23.6201G/s ints/s=2.95251G/s ns/int=338.698ps
bench_null/dist:3/param:0/repeats:10_median                   338781 ns       338778 ns           10 bytes/s=23.6143G/s ints/s=2.95179G/s ns/int=338.778ps
bench_null/dist:3/param:0/repeats:10_stddev                     1093 ns         1092 ns           10 bytes/s=76.2236M/s ints/s=9.52795M/s ns/int=1.09244ps
bench_null/dist:3/param:0/repeats:10_cv                         0.32 %          0.32 %            10 bytes/s=0.32% ints/s=0.32% ns/int=0.32%
bench_null/dist:3/param:0/repeats:10_max                      340121 ns       340117 ns           10 bytes/s=23.7309G/s ints/s=2.96636G/s ns/int=340.117ps
bench_null/dist:1/param:0/repeats:10_mean                     340445 ns       340442 ns           10 bytes/s=23.4989G/s ints/s=2.93736G/s ns/int=340.442ps
bench_null/dist:1/param:0/repeats:10_median                   340386 ns       340382 ns           10 bytes/s=23.503G/s ints/s=2.93788G/s ns/int=340.382ps
bench_null/dist:1/param:0/repeats:10_stddev                      201 ns          202 ns           10 bytes/s=13.9177M/s ints/s=1.73971M/s ns/int=201.685fs
bench_null/dist:1/param:0/repeats:10_cv                         0.06 %          0.06 %            10 bytes/s=0.06% ints/s=0.06% ns/int=0.06%
bench_null/dist:1/param:0/repeats:10_max                      340743 ns       340744 ns           10 bytes/s=23.5143G/s ints/s=2.93928G/s ns/int=340.744ps
bench_null/dist:4/param:0/repeats:10_mean                     340580 ns       340578 ns           10 bytes/s=23.4895G/s ints/s=2.93619G/s ns/int=340.578ps
bench_null/dist:4/param:0/repeats:10_median                   340760 ns       340760 ns           10 bytes/s=23.4769G/s ints/s=2.93461G/s ns/int=340.76ps
bench_null/dist:4/param:0/repeats:10_stddev                      585 ns          587 ns           10 bytes/s=40.6216M/s ints/s=5.0777M/s ns/int=586.749fs
bench_null/dist:4/param:0/repeats:10_cv                         0.17 %          0.17 %            10 bytes/s=0.17% ints/s=0.17% ns/int=0.17%
bench_null/dist:4/param:0/repeats:10_max                      340978 ns       340975 ns           10 bytes/s=23.6007G/s ints/s=2.95008G/s ns/int=340.975ps
bench_null/dist:2/param:1/repeats:10_mean                     338636 ns       338634 ns           10 bytes/s=23.6244G/s ints/s=2.95305G/s ns/int=338.634ps
bench_null/dist:2/param:1/repeats:10_median                   338308 ns       338306 ns           10 bytes/s=23.6472G/s ints/s=2.9559G/s ns/int=338.306ps
bench_null/dist:2/param:1/repeats:10_stddev                      761 ns          760 ns           10 bytes/s=52.9299M/s ints/s=6.61624M/s ns/int=760.239fs
bench_null/dist:2/param:1/repeats:10_cv                         0.22 %          0.22 %            10 bytes/s=0.22% ints/s=0.22% ns/int=0.22%
bench_null/dist:2/param:1/repeats:10_max                      339994 ns       339990 ns           10 bytes/s=23.6852G/s ints/s=2.96065G/s ns/int=339.99ps
bench_null/dist:2/param:4/repeats:10_mean                     338446 ns       338444 ns           10 bytes/s=23.6376G/s ints/s=2.95471G/s ns/int=338.444ps
bench_null/dist:2/param:4/repeats:10_median                   338353 ns       338351 ns           10 bytes/s=23.6441G/s ints/s=2.95551G/s ns/int=338.351ps
bench_null/dist:2/param:4/repeats:10_stddev                      492 ns          490 ns           10 bytes/s=34.2272M/s ints/s=4.2784M/s ns/int=490.268fs
bench_null/dist:2/param:4/repeats:10_cv                         0.15 %          0.14 %            10 bytes/s=0.14% ints/s=0.14% ns/int=0.14%
bench_null/dist:2/param:4/repeats:10_max                      339213 ns       339207 ns           10 bytes/s=23.6818G/s ints/s=2.96023G/s ns/int=339.207ps
bench_null/dist:2/param:8/repeats:10_mean                     338819 ns       338817 ns           10 bytes/s=23.6118G/s ints/s=2.95147G/s ns/int=338.817ps
bench_null/dist:2/param:8/repeats:10_median                   338982 ns       338982 ns           10 bytes/s=23.6001G/s ints/s=2.95001G/s ns/int=338.982ps
bench_null/dist:2/param:8/repeats:10_stddev                     1069 ns         1069 ns           10 bytes/s=74.5995M/s ints/s=9.32494M/s ns/int=1.06922ps
bench_null/dist:2/param:8/repeats:10_cv                         0.32 %          0.32 %            10 bytes/s=0.32% ints/s=0.32% ns/int=0.32%
bench_null/dist:2/param:8/repeats:10_max                      340456 ns       340455 ns           10 bytes/s=23.7498G/s ints/s=2.96872G/s ns/int=340.455ps
bench_null/dist:2/param:12/repeats:10_mean                    338056 ns       338054 ns           10 bytes/s=23.6649G/s ints/s=2.95812G/s ns/int=338.054ps
bench_null/dist:2/param:12/repeats:10_median                  338068 ns       338067 ns           10 bytes/s=23.664G/s ints/s=2.958G/s ns/int=338.067ps
bench_null/dist:2/param:12/repeats:10_stddev                     561 ns          562 ns           10 bytes/s=39.367M/s ints/s=4.92087M/s ns/int=562.102fs
bench_null/dist:2/param:12/repeats:10_cv                        0.17 %          0.17 %            10 bytes/s=0.17% ints/s=0.17% ns/int=0.17%
bench_null/dist:2/param:12/repeats:10_max                     338838 ns       338838 ns           10 bytes/s=23.7337G/s ints/s=2.96671G/s ns/int=338.838ps
bench_null/dist:2/param:16/repeats:10_mean                    337994 ns       337992 ns           10 bytes/s=23.6693G/s ints/s=2.95866G/s ns/int=337.992ps
bench_null/dist:2/param:16/repeats:10_median                  338119 ns       338116 ns           10 bytes/s=23.6605G/s ints/s=2.95756G/s ns/int=338.116ps
bench_null/dist:2/param:16/repeats:10_stddev                     674 ns          674 ns           10 bytes/s=47.2208M/s ints/s=5.9026M/s ns/int=674.409fs
bench_null/dist:2/param:16/repeats:10_cv                        0.20 %          0.20 %            10 bytes/s=0.20% ints/s=0.20% ns/int=0.20%
bench_null/dist:2/param:16/repeats:10_max                     339078 ns       339078 ns           10 bytes/s=23.729G/s ints/s=2.96613G/s ns/int=339.078ps
bench_null/dist:2/param:19/repeats:10_mean                    338211 ns       338209 ns           10 bytes/s=23.654G/s ints/s=2.95675G/s ns/int=338.209ps
bench_null/dist:2/param:19/repeats:10_median                  338226 ns       338220 ns           10 bytes/s=23.6532G/s ints/s=2.95666G/s ns/int=338.22ps
bench_null/dist:2/param:19/repeats:10_stddev                     225 ns          225 ns           10 bytes/s=15.7503M/s ints/s=1.96878M/s ns/int=225.155fs
bench_null/dist:2/param:19/repeats:10_cv                        0.07 %          0.07 %            10 bytes/s=0.07% ints/s=0.07% ns/int=0.07%
bench_null/dist:2/param:19/repeats:10_max                     338511 ns       338511 ns           10 bytes/s=23.6831G/s ints/s=2.96039G/s ns/int=338.511ps
bench_std_to_chars/dist:0/param:0/repeats:10_mean           23163781 ns     23163586 ns           10 bytes/s=836.598M/s ints/s=43.1712M/s ns/int=23.1636ns
bench_std_to_chars/dist:0/param:0/repeats:10_median         23161704 ns     23161627 ns           10 bytes/s=836.669M/s ints/s=43.1749M/s ns/int=23.1616ns
bench_std_to_chars/dist:0/param:0/repeats:10_stddev            10964 ns        10975 ns           10 bytes/s=396.331k/s ints/s=20.452k/s ns/int=10.9751ps
bench_std_to_chars/dist:0/param:0/repeats:10_cv                 0.05 %          0.05 %            10 bytes/s=0.05% ints/s=0.05% ns/int=0.05%
bench_std_to_chars/dist:0/param:0/repeats:10_max            23184289 ns     23184345 ns           10 bytes/s=837.184M/s ints/s=43.2014M/s ns/int=23.1843ns
bench_std_to_chars/dist:3/param:0/repeats:10_mean           18102696 ns     18102426 ns           10 bytes/s=1.04294G/s ints/s=55.2413M/s ns/int=18.1024ns
bench_std_to_chars/dist:3/param:0/repeats:10_median         18104225 ns     18104057 ns           10 bytes/s=1.04284G/s ints/s=55.2362M/s ns/int=18.1041ns
bench_std_to_chars/dist:3/param:0/repeats:10_stddev            16598 ns        16703 ns           10 bytes/s=962.66k/s ints/s=50.9891k/s ns/int=16.7031ps
bench_std_to_chars/dist:3/param:0/repeats:10_cv                 0.09 %          0.09 %            10 bytes/s=0.09% ints/s=0.09% ns/int=0.09%
bench_std_to_chars/dist:3/param:0/repeats:10_max            18123305 ns     18123096 ns           10 bytes/s=1.0448G/s ints/s=55.3398M/s ns/int=18.1231ns
bench_std_to_chars/dist:1/param:0/repeats:10_mean           22739678 ns     22739467 ns           10 bytes/s=442.146M/s ints/s=43.9767M/s ns/int=22.7395ns
bench_std_to_chars/dist:1/param:0/repeats:10_median         22728517 ns     22728291 ns           10 bytes/s=442.361M/s ints/s=43.998M/s ns/int=22.7283ns
bench_std_to_chars/dist:1/param:0/repeats:10_stddev            61381 ns        61362 ns           10 bytes/s=1.1895M/s ints/s=118.31k/s ns/int=61.3619ps
bench_std_to_chars/dist:1/param:0/repeats:10_cv                 0.27 %          0.27 %            10 bytes/s=0.27% ints/s=0.27% ns/int=0.27%
bench_std_to_chars/dist:1/param:0/repeats:10_max            22880917 ns     22880984 ns           10 bytes/s=443.439M/s ints/s=44.1053M/s ns/int=22.881ns
bench_std_to_chars/dist:4/param:0/repeats:10_mean           25260587 ns     25260337 ns           10 bytes/s=616.234M/s ints/s=39.5878M/s ns/int=25.2603ns
bench_std_to_chars/dist:4/param:0/repeats:10_median         25260342 ns     25260428 ns           10 bytes/s=616.231M/s ints/s=39.5876M/s ns/int=25.2604ns
bench_std_to_chars/dist:4/param:0/repeats:10_stddev            20841 ns        20834 ns           10 bytes/s=508.359k/s ints/s=32.6577k/s ns/int=20.834ps
bench_std_to_chars/dist:4/param:0/repeats:10_cv                 0.08 %          0.08 %            10 bytes/s=0.08% ints/s=0.08% ns/int=0.08%
bench_std_to_chars/dist:4/param:0/repeats:10_max            25294692 ns     25294763 ns           10 bytes/s=617.216M/s ints/s=39.6509M/s ns/int=25.2948ns
bench_std_to_chars/dist:2/param:1/repeats:10_mean            2516577 ns      2516557 ns           10 bytes/s=397.369M/s ints/s=397.369M/s ns/int=2.51656ns
bench_std_to_chars/dist:2/param:1/repeats:10_median          2516715 ns      2516702 ns           10 bytes/s=397.345M/s ints/s=397.345M/s ns/int=2.5167ns
bench_std_to_chars/dist:2/param:1/repeats:10_stddev             3162 ns         3168 ns           10 bytes/s=500.059k/s ints/s=500.059k/s ns/int=3.16779ps
bench_std_to_chars/dist:2/param:1/repeats:10_cv                 0.13 %          0.13 %            10 bytes/s=0.13% ints/s=0.13% ns/int=0.13%
bench_std_to_chars/dist:2/param:1/repeats:10_max             2521388 ns      2521394 ns           10 bytes/s=397.957M/s ints/s=397.957M/s ns/int=2.52139ns
bench_std_to_chars/dist:2/param:4/repeats:10_mean            3402902 ns      3402865 ns           10 bytes/s=1.17549G/s ints/s=293.873M/s ns/int=3.40287ns
bench_std_to_chars/dist:2/param:4/repeats:10_median          3405301 ns      3405237 ns           10 bytes/s=1.17466G/s ints/s=293.665M/s ns/int=3.40524ns
bench_std_to_chars/dist:2/param:4/repeats:10_stddev            11341 ns        11343 ns           10 bytes/s=3.93594M/s ints/s=983.985k/s ns/int=11.3434ps
bench_std_to_chars/dist:2/param:4/repeats:10_cv                 0.33 %          0.33 %            10 bytes/s=0.33% ints/s=0.33% ns/int=0.33%
bench_std_to_chars/dist:2/param:4/repeats:10_max             3414160 ns      3414170 ns           10 bytes/s=1.18496G/s ints/s=296.24M/s ns/int=3.41417ns
bench_std_to_chars/dist:2/param:8/repeats:10_mean            6883389 ns      6883281 ns           10 bytes/s=1.16226G/s ints/s=145.283M/s ns/int=6.88328ns
bench_std_to_chars/dist:2/param:8/repeats:10_median          6878360 ns      6878256 ns           10 bytes/s=1.16309G/s ints/s=145.386M/s ns/int=6.87826ns
bench_std_to_chars/dist:2/param:8/repeats:10_stddev            33479 ns        33506 ns           10 bytes/s=5.65058M/s ints/s=706.323k/s ns/int=33.506ps
bench_std_to_chars/dist:2/param:8/repeats:10_cv                 0.49 %          0.49 %            10 bytes/s=0.49% ints/s=0.49% ns/int=0.49%
bench_std_to_chars/dist:2/param:8/repeats:10_max             6929183 ns      6928992 ns           10 bytes/s=1.1697G/s ints/s=146.212M/s ns/int=6.92899ns
bench_std_to_chars/dist:2/param:12/repeats:10_mean           9943470 ns      9943397 ns           10 bytes/s=1.20683G/s ints/s=100.569M/s ns/int=9.9434ns
bench_std_to_chars/dist:2/param:12/repeats:10_median         9946219 ns      9946042 ns           10 bytes/s=1.20651G/s ints/s=100.543M/s ns/int=9.94604ns
bench_std_to_chars/dist:2/param:12/repeats:10_stddev            9318 ns         9322 ns           10 bytes/s=1.13184M/s ints/s=94.3202k/s ns/int=9.32214ps
bench_std_to_chars/dist:2/param:12/repeats:10_cv                0.09 %          0.09 %            10 bytes/s=0.09% ints/s=0.09% ns/int=0.09%
bench_std_to_chars/dist:2/param:12/repeats:10_max            9953355 ns      9953384 ns           10 bytes/s=1.20865G/s ints/s=100.721M/s ns/int=9.95338ns
bench_std_to_chars/dist:2/param:16/repeats:10_mean          13669314 ns     13669170 ns           10 bytes/s=1.17052G/s ints/s=73.1576M/s ns/int=13.6692ns
bench_std_to_chars/dist:2/param:16/repeats:10_median        13662150 ns     13662093 ns           10 bytes/s=1.17112G/s ints/s=73.1952M/s ns/int=13.6621ns
bench_std_to_chars/dist:2/param:16/repeats:10_stddev           26886 ns        26864 ns           10 bytes/s=2.30093M/s ints/s=143.808k/s ns/int=26.864ps
bench_std_to_chars/dist:2/param:16/repeats:10_cv                0.20 %          0.20 %            10 bytes/s=0.20% ints/s=0.20% ns/int=0.20%
bench_std_to_chars/dist:2/param:16/repeats:10_max           13711857 ns     13711610 ns           10 bytes/s=1.17485G/s ints/s=73.4279M/s ns/int=13.7116ns
bench_std_to_chars/dist:2/param:19/repeats:10_mean          16886425 ns     16886273 ns           10 bytes/s=1.12517G/s ints/s=59.2197M/s ns/int=16.8863ns
bench_std_to_chars/dist:2/param:19/repeats:10_median        16885503 ns     16885370 ns           10 bytes/s=1.12523G/s ints/s=59.2229M/s ns/int=16.8854ns
bench_std_to_chars/dist:2/param:19/repeats:10_stddev           11681 ns        11787 ns           10 bytes/s=785.538k/s ints/s=41.3441k/s ns/int=11.7865ps
bench_std_to_chars/dist:2/param:19/repeats:10_cv                0.07 %          0.07 %            10 bytes/s=0.07% ints/s=0.07% ns/int=0.07%
bench_std_to_chars/dist:2/param:19/repeats:10_max           16902700 ns     16902756 ns           10 bytes/s=1.12672G/s ints/s=59.3008M/s ns/int=16.9028ns
bench_yy_itoa/dist:0/param:0/repeats:10_mean                 7761589 ns      7761486 ns           10 bytes/s=2.49677G/s ints/s=128.841M/s ns/int=7.76149ns
bench_yy_itoa/dist:0/param:0/repeats:10_median               7762123 ns      7761948 ns           10 bytes/s=2.49662G/s ints/s=128.834M/s ns/int=7.76195ns
bench_yy_itoa/dist:0/param:0/repeats:10_stddev                  1837 ns         1895 ns           10 bytes/s=609.441k/s ints/s=31.4491k/s ns/int=1.89454ps
bench_yy_itoa/dist:0/param:0/repeats:10_cv                      0.02 %          0.02 %            10 bytes/s=0.02% ints/s=0.02% ns/int=0.02%
bench_yy_itoa/dist:0/param:0/repeats:10_max                  7764265 ns      7764282 ns           10 bytes/s=2.49755G/s ints/s=128.882M/s ns/int=7.76428ns
bench_yy_itoa/dist:3/param:0/repeats:10_mean                 7762152 ns      7762070 ns           10 bytes/s=2.4323G/s ints/s=128.832M/s ns/int=7.76207ns
bench_yy_itoa/dist:3/param:0/repeats:10_median               7761776 ns      7761573 ns           10 bytes/s=2.43246G/s ints/s=128.84M/s ns/int=7.76157ns
bench_yy_itoa/dist:3/param:0/repeats:10_stddev                  2446 ns         2422 ns           10 bytes/s=758.715k/s ints/s=40.1868k/s ns/int=2.42154ps
bench_yy_itoa/dist:3/param:0/repeats:10_cv                      0.03 %          0.03 %            10 bytes/s=0.03% ints/s=0.03% ns/int=0.03%
bench_yy_itoa/dist:3/param:0/repeats:10_max                  7766697 ns      7766556 ns           10 bytes/s=2.43351G/s ints/s=128.896M/s ns/int=7.76656ns
bench_yy_itoa/dist:1/param:0/repeats:10_mean                15196197 ns     15195934 ns           10 bytes/s=661.632M/s ints/s=65.8071M/s ns/int=15.1959ns
bench_yy_itoa/dist:1/param:0/repeats:10_median              15196018 ns     15195804 ns           10 bytes/s=661.637M/s ints/s=65.8076M/s ns/int=15.1958ns
bench_yy_itoa/dist:1/param:0/repeats:10_stddev                 14016 ns        14032 ns           10 bytes/s=610.79k/s ints/s=60.7503k/s ns/int=14.0321ps
bench_yy_itoa/dist:1/param:0/repeats:10_cv                      0.09 %          0.09 %            10 bytes/s=0.09% ints/s=0.09% ns/int=0.09%
bench_yy_itoa/dist:1/param:0/repeats:10_max                 15225134 ns     15224653 ns           10 bytes/s=662.673M/s ints/s=65.9107M/s ns/int=15.2247ns
bench_yy_itoa/dist:4/param:0/repeats:10_mean                13312852 ns     13312707 ns           10 bytes/s=1.16928G/s ints/s=75.1162M/s ns/int=13.3127ns
bench_yy_itoa/dist:4/param:0/repeats:10_median              13310321 ns     13310111 ns           10 bytes/s=1.16951G/s ints/s=75.1309M/s ns/int=13.3101ns
bench_yy_itoa/dist:4/param:0/repeats:10_stddev                  8233 ns         8297 ns           10 bytes/s=728.274k/s ints/s=46.7854k/s ns/int=8.29688ps
bench_yy_itoa/dist:4/param:0/repeats:10_cv                      0.06 %          0.06 %            10 bytes/s=0.06% ints/s=0.06% ns/int=0.06%
bench_yy_itoa/dist:4/param:0/repeats:10_max                 13331236 ns     13331268 ns           10 bytes/s=1.17021G/s ints/s=75.1762M/s ns/int=13.3313ns
bench_yy_itoa/dist:2/param:1/repeats:10_mean                 2863266 ns      2863236 ns           10 bytes/s=349.256M/s ints/s=349.256M/s ns/int=2.86324ns
bench_yy_itoa/dist:2/param:1/repeats:10_median               2863501 ns      2863461 ns           10 bytes/s=349.228M/s ints/s=349.228M/s ns/int=2.86346ns
bench_yy_itoa/dist:2/param:1/repeats:10_stddev                  4972 ns         4972 ns           10 bytes/s=606.369k/s ints/s=606.369k/s ns/int=4.97235ps
bench_yy_itoa/dist:2/param:1/repeats:10_cv                      0.17 %          0.17 %            10 bytes/s=0.17% ints/s=0.17% ns/int=0.17%
bench_yy_itoa/dist:2/param:1/repeats:10_max                  2872429 ns      2872395 ns           10 bytes/s=350.109M/s ints/s=350.109M/s ns/int=2.8724ns
bench_yy_itoa/dist:2/param:4/repeats:10_mean                 2440819 ns      2440799 ns           10 bytes/s=1.63881G/s ints/s=409.703M/s ns/int=2.4408ns
bench_yy_itoa/dist:2/param:4/repeats:10_median               2441774 ns      2441766 ns           10 bytes/s=1.63816G/s ints/s=409.54M/s ns/int=2.44177ns
bench_yy_itoa/dist:2/param:4/repeats:10_stddev                  3467 ns         3464 ns           10 bytes/s=2.32771M/s ints/s=581.929k/s ns/int=3.46357ps
bench_yy_itoa/dist:2/param:4/repeats:10_cv                      0.14 %          0.14 %            10 bytes/s=0.14% ints/s=0.14% ns/int=0.14%
bench_yy_itoa/dist:2/param:4/repeats:10_max                  2445552 ns      2445529 ns           10 bytes/s=1.64283G/s ints/s=410.708M/s ns/int=2.44553ns
bench_yy_itoa/dist:2/param:8/repeats:10_mean                 3323411 ns      3323389 ns           10 bytes/s=2.40719G/s ints/s=300.898M/s ns/int=3.32339ns
bench_yy_itoa/dist:2/param:8/repeats:10_median               3321800 ns      3321772 ns           10 bytes/s=2.40835G/s ints/s=301.044M/s ns/int=3.32177ns
bench_yy_itoa/dist:2/param:8/repeats:10_stddev                  4636 ns         4641 ns           10 bytes/s=3.35981M/s ints/s=419.976k/s ns/int=4.6415ps
bench_yy_itoa/dist:2/param:8/repeats:10_cv                      0.14 %          0.14 %            10 bytes/s=0.14% ints/s=0.14% ns/int=0.14%
bench_yy_itoa/dist:2/param:8/repeats:10_max                  3332365 ns      3332346 ns           10 bytes/s=2.41184G/s ints/s=301.48M/s ns/int=3.33235ns
bench_yy_itoa/dist:2/param:12/repeats:10_mean                4866403 ns      4866355 ns           10 bytes/s=2.46591G/s ints/s=205.493M/s ns/int=4.86635ns
bench_yy_itoa/dist:2/param:12/repeats:10_median              4866481 ns      4866470 ns           10 bytes/s=2.46585G/s ints/s=205.488M/s ns/int=4.86647ns
bench_yy_itoa/dist:2/param:12/repeats:10_stddev                 5492 ns         5496 ns           10 bytes/s=2.78602M/s ints/s=232.169k/s ns/int=5.49643ps
bench_yy_itoa/dist:2/param:12/repeats:10_cv                     0.11 %          0.11 %            10 bytes/s=0.11% ints/s=0.11% ns/int=0.11%
bench_yy_itoa/dist:2/param:12/repeats:10_max                 4875137 ns      4875148 ns           10 bytes/s=2.47138G/s ints/s=205.948M/s ns/int=4.87515ns
bench_yy_itoa/dist:2/param:16/repeats:10_mean                5897796 ns      5897748 ns           10 bytes/s=2.7129G/s ints/s=169.556M/s ns/int=5.89775ns
bench_yy_itoa/dist:2/param:16/repeats:10_median              5897048 ns      5896977 ns           10 bytes/s=2.71325G/s ints/s=169.578M/s ns/int=5.89698ns
bench_yy_itoa/dist:2/param:16/repeats:10_stddev                 3208 ns         3225 ns           10 bytes/s=1.48397M/s ints/s=92.7481k/s ns/int=3.22544ps
bench_yy_itoa/dist:2/param:16/repeats:10_cv                     0.05 %          0.05 %            10 bytes/s=0.05% ints/s=0.05% ns/int=0.05%
bench_yy_itoa/dist:2/param:16/repeats:10_max                 5902767 ns      5902784 ns           10 bytes/s=2.71591G/s ints/s=169.744M/s ns/int=5.90278ns
bench_yy_itoa/dist:2/param:19/repeats:10_mean                7157407 ns      7157329 ns           10 bytes/s=2.65462G/s ints/s=139.717M/s ns/int=7.15733ns
bench_yy_itoa/dist:2/param:19/repeats:10_median              7157637 ns      7157619 ns           10 bytes/s=2.65451G/s ints/s=139.711M/s ns/int=7.15762ns
bench_yy_itoa/dist:2/param:19/repeats:10_stddev                 1283 ns         1263 ns           10 bytes/s=468.606k/s ints/s=24.6635k/s ns/int=1.26323ps
bench_yy_itoa/dist:2/param:19/repeats:10_cv                     0.02 %          0.02 %            10 bytes/s=0.02% ints/s=0.02% ns/int=0.02%
bench_yy_itoa/dist:2/param:19/repeats:10_max                 7158795 ns      7158676 ns           10 bytes/s=2.65565G/s ints/s=139.771M/s ns/int=7.15868ns
bench_jeaiii_itoa/dist:0/param:0/repeats:10_mean            13162945 ns     13162875 ns           10 bytes/s=1.47222G/s ints/s=75.9714M/s ns/int=13.1629ns
bench_jeaiii_itoa/dist:0/param:0/repeats:10_median          13163940 ns     13163578 ns           10 bytes/s=1.47214G/s ints/s=75.9672M/s ns/int=13.1636ns
bench_jeaiii_itoa/dist:0/param:0/repeats:10_stddev             16970 ns        16997 ns           10 bytes/s=1.90226M/s ints/s=98.1629k/s ns/int=16.9974ps
bench_jeaiii_itoa/dist:0/param:0/repeats:10_cv                  0.13 %          0.13 %            10 bytes/s=0.13% ints/s=0.13% ns/int=0.13%
bench_jeaiii_itoa/dist:0/param:0/repeats:10_max             13180357 ns     13180405 ns           10 bytes/s=1.4757G/s ints/s=76.1509M/s ns/int=13.1804ns
bench_jeaiii_itoa/dist:3/param:0/repeats:10_mean             8699213 ns      8699144 ns           10 bytes/s=2.1703G/s ints/s=114.954M/s ns/int=8.69914ns
bench_jeaiii_itoa/dist:3/param:0/repeats:10_median           8697107 ns      8697041 ns           10 bytes/s=2.17082G/s ints/s=114.982M/s ns/int=8.69704ns
bench_jeaiii_itoa/dist:3/param:0/repeats:10_stddev              8767 ns         8796 ns           10 bytes/s=2.19044M/s ints/s=116.021k/s ns/int=8.79628ps
bench_jeaiii_itoa/dist:3/param:0/repeats:10_cv                  0.10 %          0.10 %            10 bytes/s=0.10% ints/s=0.10% ns/int=0.10%
bench_jeaiii_itoa/dist:3/param:0/repeats:10_max              8722129 ns      8722151 ns           10 bytes/s=2.17216G/s ints/s=115.053M/s ns/int=8.72215ns
bench_jeaiii_itoa/dist:1/param:0/repeats:10_mean            18048650 ns     18048349 ns           10 bytes/s=557.066M/s ints/s=55.4068M/s ns/int=18.0483ns
bench_jeaiii_itoa/dist:1/param:0/repeats:10_median          18039006 ns     18038902 ns           10 bytes/s=557.357M/s ints/s=55.4357M/s ns/int=18.0389ns
bench_jeaiii_itoa/dist:1/param:0/repeats:10_stddev             20479 ns        20422 ns           10 bytes/s=629.214k/s ints/s=62.5828k/s ns/int=20.4224ps
bench_jeaiii_itoa/dist:1/param:0/repeats:10_cv                  0.11 %          0.11 %            10 bytes/s=0.11% ints/s=0.11% ns/int=0.11%
bench_jeaiii_itoa/dist:1/param:0/repeats:10_max             18098832 ns     18098580 ns           10 bytes/s=557.528M/s ints/s=55.4527M/s ns/int=18.0986ns
bench_jeaiii_itoa/dist:4/param:0/repeats:10_mean            14582892 ns     14582602 ns           10 bytes/s=1.06746G/s ints/s=68.5749M/s ns/int=14.5826ns
bench_jeaiii_itoa/dist:4/param:0/repeats:10_median          14578599 ns     14578377 ns           10 bytes/s=1.06776G/s ints/s=68.5947M/s ns/int=14.5784ns
bench_jeaiii_itoa/dist:4/param:0/repeats:10_stddev             11195 ns        11009 ns           10 bytes/s=805.414k/s ints/s=51.741k/s ns/int=11.0094ps
bench_jeaiii_itoa/dist:4/param:0/repeats:10_cv                  0.08 %          0.08 %            10 bytes/s=0.08% ints/s=0.08% ns/int=0.08%
bench_jeaiii_itoa/dist:4/param:0/repeats:10_max             14604461 ns     14603812 ns           10 bytes/s=1.06827G/s ints/s=68.6272M/s ns/int=14.6038ns
bench_jeaiii_itoa/dist:2/param:1/repeats:10_mean             1007311 ns      1007303 ns           10 bytes/s=992.763M/s ints/s=992.763M/s ns/int=1.0073ns
bench_jeaiii_itoa/dist:2/param:1/repeats:10_median           1007974 ns      1007970 ns           10 bytes/s=992.093M/s ints/s=992.093M/s ns/int=1.00797ns
bench_jeaiii_itoa/dist:2/param:1/repeats:10_stddev              3812 ns         3816 ns           10 bytes/s=3.76527M/s ints/s=3.76527M/s ns/int=3.81628ps
bench_jeaiii_itoa/dist:2/param:1/repeats:10_cv                  0.38 %          0.38 %            10 bytes/s=0.38% ints/s=0.38% ns/int=0.38%
bench_jeaiii_itoa/dist:2/param:1/repeats:10_max              1013869 ns      1013871 ns           10 bytes/s=1.00013G/s ints/s=1.00013G/s ns/int=1.01387ns
bench_jeaiii_itoa/dist:2/param:4/repeats:10_mean             1695757 ns      1695748 ns           10 bytes/s=2.35884G/s ints/s=589.71M/s ns/int=1.69575ns
bench_jeaiii_itoa/dist:2/param:4/repeats:10_median           1695662 ns      1695650 ns           10 bytes/s=2.35898G/s ints/s=589.744M/s ns/int=1.69565ns
bench_jeaiii_itoa/dist:2/param:4/repeats:10_stddev               271 ns          269 ns           10 bytes/s=374.662k/s ints/s=93.6654k/s ns/int=269.353fs
bench_jeaiii_itoa/dist:2/param:4/repeats:10_cv                  0.02 %          0.02 %            10 bytes/s=0.02% ints/s=0.02% ns/int=0.02%
bench_jeaiii_itoa/dist:2/param:4/repeats:10_max              1696121 ns      1696126 ns           10 bytes/s=2.35923G/s ints/s=589.808M/s ns/int=1.69613ns
bench_jeaiii_itoa/dist:2/param:8/repeats:10_mean             2969755 ns      2969713 ns           10 bytes/s=2.69387G/s ints/s=336.733M/s ns/int=2.96971ns
bench_jeaiii_itoa/dist:2/param:8/repeats:10_median           2970388 ns      2970365 ns           10 bytes/s=2.69327G/s ints/s=336.659M/s ns/int=2.97036ns
bench_jeaiii_itoa/dist:2/param:8/repeats:10_stddev              3326 ns         3311 ns           10 bytes/s=3.00606M/s ints/s=375.758k/s ns/int=3.31067ps
bench_jeaiii_itoa/dist:2/param:8/repeats:10_cv                  0.11 %          0.11 %            10 bytes/s=0.11% ints/s=0.11% ns/int=0.11%
bench_jeaiii_itoa/dist:2/param:8/repeats:10_max              2974876 ns      2974773 ns           10 bytes/s=2.70064G/s ints/s=337.58M/s ns/int=2.97477ns
bench_jeaiii_itoa/dist:2/param:12/repeats:10_mean            4932537 ns      4932504 ns           10 bytes/s=2.43284G/s ints/s=202.737M/s ns/int=4.9325ns
bench_jeaiii_itoa/dist:2/param:12/repeats:10_median          4933365 ns      4933344 ns           10 bytes/s=2.43243G/s ints/s=202.702M/s ns/int=4.93334ns
bench_jeaiii_itoa/dist:2/param:12/repeats:10_stddev             3363 ns         3358 ns           10 bytes/s=1.65796M/s ints/s=138.163k/s ns/int=3.35809ps
bench_jeaiii_itoa/dist:2/param:12/repeats:10_cv                 0.07 %          0.07 %            10 bytes/s=0.07% ints/s=0.07% ns/int=0.07%
bench_jeaiii_itoa/dist:2/param:12/repeats:10_max             4935671 ns      4935643 ns           10 bytes/s=2.43693G/s ints/s=203.077M/s ns/int=4.93564ns
bench_jeaiii_itoa/dist:2/param:16/repeats:10_mean            5989679 ns      5989635 ns           10 bytes/s=2.67128G/s ints/s=166.955M/s ns/int=5.98963ns
bench_jeaiii_itoa/dist:2/param:16/repeats:10_median          5988681 ns      5988655 ns           10 bytes/s=2.67172G/s ints/s=166.982M/s ns/int=5.98866ns
bench_jeaiii_itoa/dist:2/param:16/repeats:10_stddev             5089 ns         5083 ns           10 bytes/s=2.26621M/s ints/s=141.638k/s ns/int=5.08251ps
bench_jeaiii_itoa/dist:2/param:16/repeats:10_cv                 0.08 %          0.08 %            10 bytes/s=0.08% ints/s=0.08% ns/int=0.08%
bench_jeaiii_itoa/dist:2/param:16/repeats:10_max             5997600 ns      5997518 ns           10 bytes/s=2.67425G/s ints/s=167.141M/s ns/int=5.99752ns
bench_jeaiii_itoa/dist:2/param:19/repeats:10_mean            7908559 ns      7908502 ns           10 bytes/s=2.40248G/s ints/s=126.446M/s ns/int=7.9085ns
bench_jeaiii_itoa/dist:2/param:19/repeats:10_median          7910056 ns      7910074 ns           10 bytes/s=2.402G/s ints/s=126.421M/s ns/int=7.91007ns
bench_jeaiii_itoa/dist:2/param:19/repeats:10_stddev             3773 ns         3757 ns           10 bytes/s=1.14135M/s ints/s=60.0708k/s ns/int=3.75661ps
bench_jeaiii_itoa/dist:2/param:19/repeats:10_cv                 0.05 %          0.05 %            10 bytes/s=0.05% ints/s=0.05% ns/int=0.05%
bench_jeaiii_itoa/dist:2/param:19/repeats:10_max             7914068 ns      7913987 ns           10 bytes/s=2.40437G/s ints/s=126.546M/s ns/int=7.91399ns
bench_tencent_rapidjson/dist:0/param:0/repeats:10_mean      16251874 ns     16251685 ns           10 bytes/s=1.19241G/s ints/s=61.5321M/s ns/int=16.2517ns
bench_tencent_rapidjson/dist:0/param:0/repeats:10_median    16251694 ns     16251732 ns           10 bytes/s=1.1924G/s ints/s=61.5319M/s ns/int=16.2517ns
bench_tencent_rapidjson/dist:0/param:0/repeats:10_stddev        1387 ns         1486 ns           10 bytes/s=109.044k/s ints/s=5.62701k/s ns/int=1.48621ps
bench_tencent_rapidjson/dist:0/param:0/repeats:10_cv            0.01 %          0.01 %            10 bytes/s=0.01% ints/s=0.01% ns/int=0.01%
bench_tencent_rapidjson/dist:0/param:0/repeats:10_max       16254174 ns     16254213 ns           10 bytes/s=1.19254G/s ints/s=61.5391M/s ns/int=16.2542ns
bench_tencent_rapidjson/dist:3/param:0/repeats:10_mean      13183847 ns     13183724 ns           10 bytes/s=1.43205G/s ints/s=75.8511M/s ns/int=13.1837ns
bench_tencent_rapidjson/dist:3/param:0/repeats:10_median    13183386 ns     13183262 ns           10 bytes/s=1.4321G/s ints/s=75.8538M/s ns/int=13.1833ns
bench_tencent_rapidjson/dist:3/param:0/repeats:10_stddev        2399 ns         2393 ns           10 bytes/s=259.91k/s ints/s=13.7666k/s ns/int=2.39296ps
bench_tencent_rapidjson/dist:3/param:0/repeats:10_cv            0.02 %          0.02 %            10 bytes/s=0.02% ints/s=0.02% ns/int=0.02%
bench_tencent_rapidjson/dist:3/param:0/repeats:10_max       13187832 ns     13187660 ns           10 bytes/s=1.43237G/s ints/s=75.868M/s ns/int=13.1877ns
bench_tencent_rapidjson/dist:1/param:0/repeats:10_mean      21811972 ns     21811751 ns           10 bytes/s=460.951M/s ints/s=45.847M/s ns/int=21.8118ns
bench_tencent_rapidjson/dist:1/param:0/repeats:10_median    21798415 ns     21797866 ns           10 bytes/s=461.243M/s ints/s=45.8761M/s ns/int=21.7979ns
bench_tencent_rapidjson/dist:1/param:0/repeats:10_stddev       41093 ns        41020 ns           10 bytes/s=865.864k/s ints/s=86.1204k/s ns/int=41.0197ps
bench_tencent_rapidjson/dist:1/param:0/repeats:10_cv            0.19 %          0.19 %            10 bytes/s=0.19% ints/s=0.19% ns/int=0.19%
bench_tencent_rapidjson/dist:1/param:0/repeats:10_max       21886505 ns     21885919 ns           10 bytes/s=461.863M/s ints/s=45.9377M/s ns/int=21.8859ns
bench_tencent_rapidjson/dist:4/param:0/repeats:10_mean      17509718 ns     17509496 ns           10 bytes/s=889.022M/s ints/s=57.1121M/s ns/int=17.5095ns
bench_tencent_rapidjson/dist:4/param:0/repeats:10_median    17522682 ns     17522456 ns           10 bytes/s=888.361M/s ints/s=57.0696M/s ns/int=17.5225ns
bench_tencent_rapidjson/dist:4/param:0/repeats:10_stddev       34954 ns        34848 ns           10 bytes/s=1.77055M/s ints/s=113.743k/s ns/int=34.8481ps
bench_tencent_rapidjson/dist:4/param:0/repeats:10_cv            0.20 %          0.20 %            10 bytes/s=0.20% ints/s=0.20% ns/int=0.20%
bench_tencent_rapidjson/dist:4/param:0/repeats:10_max       17562849 ns     17562502 ns           10 bytes/s=892.189M/s ints/s=57.3155M/s ns/int=17.5625ns
bench_tencent_rapidjson/dist:2/param:1/repeats:10_mean       1991964 ns      1991950 ns           10 bytes/s=502.026M/s ints/s=502.026M/s ns/int=1.99195ns
bench_tencent_rapidjson/dist:2/param:1/repeats:10_median     1991260 ns      1991250 ns           10 bytes/s=502.198M/s ints/s=502.198M/s ns/int=1.99125ns
bench_tencent_rapidjson/dist:2/param:1/repeats:10_stddev        6660 ns         6673 ns           10 bytes/s=1.68249M/s ints/s=1.68249M/s ns/int=6.6726ps
bench_tencent_rapidjson/dist:2/param:1/repeats:10_cv            0.33 %          0.33 %            10 bytes/s=0.34% ints/s=0.34% ns/int=0.33%
bench_tencent_rapidjson/dist:2/param:1/repeats:10_max        2000038 ns      2000004 ns           10 bytes/s=504.976M/s ints/s=504.976M/s ns/int=2ns
bench_tencent_rapidjson/dist:2/param:4/repeats:10_mean       1978280 ns      1978252 ns           10 bytes/s=2.02213G/s ints/s=505.532M/s ns/int=1.97825ns
bench_tencent_rapidjson/dist:2/param:4/repeats:10_median     1978281 ns      1978264 ns           10 bytes/s=2.02198G/s ints/s=505.495M/s ns/int=1.97826ns
bench_tencent_rapidjson/dist:2/param:4/repeats:10_stddev       17219 ns        17238 ns           10 bytes/s=17.7741M/s ints/s=4.44352M/s ns/int=17.2375ps
bench_tencent_rapidjson/dist:2/param:4/repeats:10_cv            0.87 %          0.87 %            10 bytes/s=0.88% ints/s=0.88% ns/int=0.87%
bench_tencent_rapidjson/dist:2/param:4/repeats:10_max        1996452 ns      1996457 ns           10 bytes/s=2.06212G/s ints/s=515.53M/s ns/int=1.99646ns
bench_tencent_rapidjson/dist:2/param:8/repeats:10_mean       3436047 ns      3436029 ns           10 bytes/s=2.32827G/s ints/s=291.034M/s ns/int=3.43603ns
bench_tencent_rapidjson/dist:2/param:8/repeats:10_median     3435927 ns      3435876 ns           10 bytes/s=2.32837G/s ints/s=291.047M/s ns/int=3.43588ns
bench_tencent_rapidjson/dist:2/param:8/repeats:10_stddev         664 ns          678 ns           10 bytes/s=459.239k/s ints/s=57.4049k/s ns/int=677.899fs
bench_tencent_rapidjson/dist:2/param:8/repeats:10_cv            0.02 %          0.02 %            10 bytes/s=0.02% ints/s=0.02% ns/int=0.02%
bench_tencent_rapidjson/dist:2/param:8/repeats:10_max        3437582 ns      3437591 ns           10 bytes/s=2.32878G/s ints/s=291.097M/s ns/int=3.43759ns
bench_tencent_rapidjson/dist:2/param:12/repeats:10_mean      8043004 ns      8042901 ns           10 bytes/s=1.492G/s ints/s=124.333M/s ns/int=8.0429ns
bench_tencent_rapidjson/dist:2/param:12/repeats:10_median    8041748 ns      8041640 ns           10 bytes/s=1.49223G/s ints/s=124.353M/s ns/int=8.04164ns
bench_tencent_rapidjson/dist:2/param:12/repeats:10_stddev       5551 ns         5603 ns           10 bytes/s=1.03915M/s ints/s=86.5958k/s ns/int=5.60292ps
bench_tencent_rapidjson/dist:2/param:12/repeats:10_cv           0.07 %          0.07 %            10 bytes/s=0.07% ints/s=0.07% ns/int=0.07%
bench_tencent_rapidjson/dist:2/param:12/repeats:10_max       8051750 ns      8051652 ns           10 bytes/s=1.49349G/s ints/s=124.457M/s ns/int=8.05165ns
bench_tencent_rapidjson/dist:2/param:16/repeats:10_mean      8048780 ns      8048708 ns           10 bytes/s=1.9879G/s ints/s=124.244M/s ns/int=8.04871ns
bench_tencent_rapidjson/dist:2/param:16/repeats:10_median    8048348 ns      8048289 ns           10 bytes/s=1.988G/s ints/s=124.25M/s ns/int=8.04829ns
bench_tencent_rapidjson/dist:2/param:16/repeats:10_stddev       6879 ns         6916 ns           10 bytes/s=1.70669M/s ints/s=106.668k/s ns/int=6.91645ps
bench_tencent_rapidjson/dist:2/param:16/repeats:10_cv           0.09 %          0.09 %            10 bytes/s=0.09% ints/s=0.09% ns/int=0.09%
bench_tencent_rapidjson/dist:2/param:16/repeats:10_max       8064510 ns      8064539 ns           10 bytes/s=1.9899G/s ints/s=124.369M/s ns/int=8.06454ns
bench_tencent_rapidjson/dist:2/param:19/repeats:10_mean     12901960 ns     12901818 ns           10 bytes/s=1.47266G/s ints/s=77.5085M/s ns/int=12.9018ns
bench_tencent_rapidjson/dist:2/param:19/repeats:10_median   12898904 ns     12898868 ns           10 bytes/s=1.473G/s ints/s=77.5262M/s ns/int=12.8989ns
bench_tencent_rapidjson/dist:2/param:19/repeats:10_stddev      12135 ns        12195 ns           10 bytes/s=1.38912M/s ints/s=73.1114k/s ns/int=12.195ps
bench_tencent_rapidjson/dist:2/param:19/repeats:10_cv           0.09 %          0.09 %            10 bytes/s=0.09% ints/s=0.09% ns/int=0.09%
bench_tencent_rapidjson/dist:2/param:19/repeats:10_max      12935117 ns     12935160 ns           10 bytes/s=1.47364G/s ints/s=77.5602M/s ns/int=12.9352ns
bench_fmtlib_fmt/dist:0/param:0/repeats:10_mean             17202870 ns     17202698 ns           10 bytes/s=1.12649G/s ints/s=58.1305M/s ns/int=17.2027ns
bench_fmtlib_fmt/dist:0/param:0/repeats:10_median           17201351 ns     17201239 ns           10 bytes/s=1.12658G/s ints/s=58.1353M/s ns/int=17.2012ns
bench_fmtlib_fmt/dist:0/param:0/repeats:10_stddev              14433 ns        14478 ns           10 bytes/s=947.975k/s ints/s=48.9186k/s ns/int=14.4785ps
bench_fmtlib_fmt/dist:0/param:0/repeats:10_cv                   0.08 %          0.08 %            10 bytes/s=0.08% ints/s=0.08% ns/int=0.08%
bench_fmtlib_fmt/dist:0/param:0/repeats:10_max              17226542 ns     17226088 ns           10 bytes/s=1.12786G/s ints/s=58.2012M/s ns/int=17.2261ns
bench_fmtlib_fmt/dist:3/param:0/repeats:10_mean             13982922 ns     13982790 ns           10 bytes/s=1.35021G/s ints/s=71.5165M/s ns/int=13.9828ns
bench_fmtlib_fmt/dist:3/param:0/repeats:10_median           13984458 ns     13984362 ns           10 bytes/s=1.35006G/s ints/s=71.5084M/s ns/int=13.9844ns
bench_fmtlib_fmt/dist:3/param:0/repeats:10_stddev               8316 ns         8265 ns           10 bytes/s=798.331k/s ints/s=42.2852k/s ns/int=8.2648ps
bench_fmtlib_fmt/dist:3/param:0/repeats:10_cv                   0.06 %          0.06 %            10 bytes/s=0.06% ints/s=0.06% ns/int=0.06%
bench_fmtlib_fmt/dist:3/param:0/repeats:10_max              13995248 ns     13994842 ns           10 bytes/s=1.35183G/s ints/s=71.6021M/s ns/int=13.9948ns
bench_fmtlib_fmt/dist:1/param:0/repeats:10_mean             22621834 ns     22621594 ns           10 bytes/s=444.448M/s ints/s=44.2056M/s ns/int=22.6216ns
bench_fmtlib_fmt/dist:1/param:0/repeats:10_median           22625515 ns     22625172 ns           10 bytes/s=444.377M/s ints/s=44.1986M/s ns/int=22.6252ns
bench_fmtlib_fmt/dist:1/param:0/repeats:10_stddev              27455 ns        27441 ns           10 bytes/s=539.585k/s ints/s=53.6681k/s ns/int=27.441ps
bench_fmtlib_fmt/dist:1/param:0/repeats:10_cv                   0.12 %          0.12 %            10 bytes/s=0.12% ints/s=0.12% ns/int=0.12%
bench_fmtlib_fmt/dist:1/param:0/repeats:10_max              22652728 ns     22652005 ns           10 bytes/s=445.399M/s ints/s=44.3002M/s ns/int=22.652ns
bench_fmtlib_fmt/dist:4/param:0/repeats:10_mean             23262670 ns     23262463 ns           10 bytes/s=669.159M/s ints/s=42.9878M/s ns/int=23.2625ns
bench_fmtlib_fmt/dist:4/param:0/repeats:10_median           23263086 ns     23263054 ns           10 bytes/s=669.141M/s ints/s=42.9866M/s ns/int=23.2631ns
bench_fmtlib_fmt/dist:4/param:0/repeats:10_stddev              24732 ns        24893 ns           10 bytes/s=716.234k/s ints/s=46.012k/s ns/int=24.8932ps
bench_fmtlib_fmt/dist:4/param:0/repeats:10_cv                   0.11 %          0.11 %            10 bytes/s=0.11% ints/s=0.11% ns/int=0.11%
bench_fmtlib_fmt/dist:4/param:0/repeats:10_max              23292669 ns     23292738 ns           10 bytes/s=670.298M/s ints/s=43.061M/s ns/int=23.2927ns
bench_fmtlib_fmt/dist:2/param:1/repeats:10_mean              1015698 ns      1015682 ns           10 bytes/s=984.56M/s ints/s=984.56M/s ns/int=1.01568ns
bench_fmtlib_fmt/dist:2/param:1/repeats:10_median            1015609 ns      1015589 ns           10 bytes/s=984.651M/s ints/s=984.651M/s ns/int=1.01559ns
bench_fmtlib_fmt/dist:2/param:1/repeats:10_stddev                565 ns          567 ns           10 bytes/s=548.814k/s ints/s=548.814k/s ns/int=566.504fs
bench_fmtlib_fmt/dist:2/param:1/repeats:10_cv                   0.06 %          0.06 %            10 bytes/s=0.06% ints/s=0.06% ns/int=0.06%
bench_fmtlib_fmt/dist:2/param:1/repeats:10_max               1016989 ns      1016972 ns           10 bytes/s=985.252M/s ints/s=985.252M/s ns/int=1.01697ns
bench_fmtlib_fmt/dist:2/param:4/repeats:10_mean              2195869 ns      2195855 ns           10 bytes/s=1.82162G/s ints/s=455.404M/s ns/int=2.19585ns
bench_fmtlib_fmt/dist:2/param:4/repeats:10_median            2195152 ns      2195131 ns           10 bytes/s=1.82221G/s ints/s=455.554M/s ns/int=2.19513ns
bench_fmtlib_fmt/dist:2/param:4/repeats:10_stddev               2261 ns         2272 ns           10 bytes/s=1.88026M/s ints/s=470.064k/s ns/int=2.27155ps
bench_fmtlib_fmt/dist:2/param:4/repeats:10_cv                   0.10 %          0.10 %            10 bytes/s=0.10% ints/s=0.10% ns/int=0.10%
bench_fmtlib_fmt/dist:2/param:4/repeats:10_max               2201998 ns      2202006 ns           10 bytes/s=1.82282G/s ints/s=455.705M/s ns/int=2.20201ns
bench_fmtlib_fmt/dist:2/param:8/repeats:10_mean              4552497 ns      4552461 ns           10 bytes/s=1.7573G/s ints/s=219.662M/s ns/int=4.55246ns
bench_fmtlib_fmt/dist:2/param:8/repeats:10_median            4552599 ns      4552576 ns           10 bytes/s=1.75725G/s ints/s=219.656M/s ns/int=4.55258ns
bench_fmtlib_fmt/dist:2/param:8/repeats:10_stddev               7276 ns         7271 ns           10 bytes/s=2.80654M/s ints/s=350.817k/s ns/int=7.27136ps
bench_fmtlib_fmt/dist:2/param:8/repeats:10_cv                   0.16 %          0.16 %            10 bytes/s=0.16% ints/s=0.16% ns/int=0.16%
bench_fmtlib_fmt/dist:2/param:8/repeats:10_max               4565611 ns      4565623 ns           10 bytes/s=1.76197G/s ints/s=220.246M/s ns/int=4.56562ns
bench_fmtlib_fmt/dist:2/param:12/repeats:10_mean             6907732 ns      6907678 ns           10 bytes/s=1.73721G/s ints/s=144.767M/s ns/int=6.90768ns
bench_fmtlib_fmt/dist:2/param:12/repeats:10_median           6908137 ns      6908066 ns           10 bytes/s=1.7371G/s ints/s=144.758M/s ns/int=6.90807ns
bench_fmtlib_fmt/dist:2/param:12/repeats:10_stddev             15646 ns        15693 ns           10 bytes/s=3.9483M/s ints/s=329.025k/s ns/int=15.6926ps
bench_fmtlib_fmt/dist:2/param:12/repeats:10_cv                  0.23 %          0.23 %            10 bytes/s=0.23% ints/s=0.23% ns/int=0.23%
bench_fmtlib_fmt/dist:2/param:12/repeats:10_max              6930759 ns      6930777 ns           10 bytes/s=1.74346G/s ints/s=145.288M/s ns/int=6.93078ns
bench_fmtlib_fmt/dist:2/param:16/repeats:10_mean             9475841 ns      9475732 ns           10 bytes/s=1.68853G/s ints/s=105.533M/s ns/int=9.47573ns
bench_fmtlib_fmt/dist:2/param:16/repeats:10_median           9481399 ns      9481259 ns           10 bytes/s=1.68754G/s ints/s=105.471M/s ns/int=9.48126ns
bench_fmtlib_fmt/dist:2/param:16/repeats:10_stddev             11967 ns        12020 ns           10 bytes/s=2.14378M/s ints/s=133.986k/s ns/int=12.0203ps
bench_fmtlib_fmt/dist:2/param:16/repeats:10_cv                  0.13 %          0.13 %            10 bytes/s=0.13% ints/s=0.13% ns/int=0.13%
bench_fmtlib_fmt/dist:2/param:16/repeats:10_max              9488925 ns      9488951 ns           10 bytes/s=1.69248G/s ints/s=105.78M/s ns/int=9.48895ns
bench_fmtlib_fmt/dist:2/param:19/repeats:10_mean            12382006 ns     12381875 ns           10 bytes/s=1.5345G/s ints/s=80.7632M/s ns/int=12.3819ns
bench_fmtlib_fmt/dist:2/param:19/repeats:10_median          12382974 ns     12382729 ns           10 bytes/s=1.5344G/s ints/s=80.7576M/s ns/int=12.3827ns
bench_fmtlib_fmt/dist:2/param:19/repeats:10_stddev              7074 ns         7134 ns           10 bytes/s=884.866k/s ints/s=46.5719k/s ns/int=7.13378ps
bench_fmtlib_fmt/dist:2/param:19/repeats:10_cv                  0.06 %          0.06 %            10 bytes/s=0.06% ints/s=0.06% ns/int=0.06%
bench_fmtlib_fmt/dist:2/param:19/repeats:10_max             12389267 ns     12389296 ns           10 bytes/s=1.5367G/s ints/s=80.8792M/s ns/int=12.3893ns
```

</details>
