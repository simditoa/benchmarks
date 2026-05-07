# Benchmark results

_Generated 2026-05-07 on a GCP `c3-standard-8` VM in `us-central1-a`._

_Summary produced by OpenAI `gpt-4.1`. Numbers are sourced from the raw google/benchmark output included at the bottom of this file._

- **Fastest overall:** `yy_itoa` is the fastest real implementation on UNIFORM (128.636M ints/s), LOG (67.195M ints/s), and all FIXED distributions.
- **Best for short fixed lengths:** `jeaiii_itoa` leads for FIXED:1 (744.322M ints/s) and FIXED:4 (589.255M ints/s), but is surpassed by `yy_itoa` for longer lengths.
- **Notable outliers:** `std_to_chars` and `fmtlib_fmt` are consistently slower than other real implementations across all distributions.
- **Null baseline:** The `null` benchmark (no conversion) is 20x+ faster than any real implementation, as expected.
- **Hardware caveat:** AVX-512 IFMA/VBMI are present, so all contenders, including `simditoa`, run their full optimized code paths.

| Contender            | UNIFORM ints/s | LOG ints/s | FIXED:8 ints/s | FIXED:19 ints/s |
|----------------------|----------------|------------|----------------|-----------------|
| yy_itoa              | 128,636,000    | 67,195,100 | 298,543,000    | 139,748,000     |
| simditoa_to_chars    | 101,161,000    | 80,630,000 | 225,330,000    | 184,635,000     |
| jeaiii_itoa          | 74,698,400     | 56,111,800 | 342,882,000    | 127,697,000     |
| tencent_rapidjson    | 61,807,900     | 45,761,600 | 291,376,000    | 77,352,500      |
| fmtlib_fmt           | 58,926,600     | 45,080,800 | 220,446,000    | 80,524,800      |
| std_to_chars         | 42,005,700     | 43,968,000 | 146,086,000    | 56,573,800      |
| null                 | 2,712,230,000  | 2,680,690,000 | 2,666,310,000 | 2,745,460,000   |

| Contender         | FIXED:1 ints/s | FIXED:4 ints/s | FIXED:8 ints/s | FIXED:12 ints/s | FIXED:16 ints/s | FIXED:19 ints/s |
|-------------------|----------------|----------------|----------------|-----------------|-----------------|-----------------|
| yy_itoa           | 548,328,000    | 422,272,000    | 298,543,000    | 205,557,000     | 169,522,000     | 139,748,000     |
| jeaiii_itoa       | 744,322,000    | 589,255,000    | 342,882,000    | 202,657,000     | 166,921,000     | 127,697,000     |
| simditoa_to_chars | 270,306,000    | 225,362,000    | 225,330,000    | 189,808,000     | 189,697,000     | 184,635,000     |
| tencent_rapidjson | 491,407,000    | 510,604,000    | 291,376,000    | 124,416,000     | 124,326,000     | 77,352,500      |
| fmtlib_fmt        | 984,985,000    | 444,063,000    | 220,446,000    | 134,052,000     | 105,470,000     | 80,524,800      |
| std_to_chars      | 350,997,000    | 325,227,000    | 146,086,000    | 95,707,200      | 71,527,900      | 56,573,800      |
| null              | 2,536,100,000  | 2,565,630,000  | 2,666,310,000  | 2,930,860,000   | 2,964,750,000   | 2,745,460,000   |

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
bench_simditoa_to_chars/dist:0/param:0/repeats:10_mean       9886878 ns      9885269 ns           10 bytes/s=1.96035G/s ints/s=101.161M/s ns/int=9.88527ns
bench_simditoa_to_chars/dist:0/param:0/repeats:10_median     9888842 ns      9886823 ns           10 bytes/s=1.96004G/s ints/s=101.145M/s ns/int=9.88682ns
bench_simditoa_to_chars/dist:0/param:0/repeats:10_stddev        6602 ns         6466 ns           10 bytes/s=1.28262M/s ints/s=66.1875k/s ns/int=6.46623ps
bench_simditoa_to_chars/dist:0/param:0/repeats:10_cv            0.07 %          0.07 %            10 bytes/s=0.07% ints/s=0.07% ns/int=0.07%
bench_simditoa_to_chars/dist:0/param:0/repeats:10_max        9893968 ns      9891460 ns           10 bytes/s=1.96242G/s ints/s=101.268M/s ns/int=9.89146ns
bench_simditoa_to_chars/dist:1/param:0/repeats:10_mean      12404455 ns     12402371 ns           10 bytes/s=810.662M/s ints/s=80.63M/s ns/int=12.4024ns
bench_simditoa_to_chars/dist:1/param:0/repeats:10_median    12401882 ns     12400258 ns           10 bytes/s=810.798M/s ints/s=80.6435M/s ns/int=12.4003ns
bench_simditoa_to_chars/dist:1/param:0/repeats:10_stddev       21737 ns        21198 ns           10 bytes/s=1.38439M/s ints/s=137.694k/s ns/int=21.1975ps
bench_simditoa_to_chars/dist:1/param:0/repeats:10_cv            0.18 %          0.17 %            10 bytes/s=0.17% ints/s=0.17% ns/int=0.17%
bench_simditoa_to_chars/dist:1/param:0/repeats:10_max       12443263 ns     12440319 ns           10 bytes/s=812.514M/s ints/s=80.8142M/s ns/int=12.4403ns
bench_simditoa_to_chars/dist:2/param:1/repeats:10_mean       3699866 ns      3699513 ns           10 bytes/s=270.306M/s ints/s=270.306M/s ns/int=3.69951ns
bench_simditoa_to_chars/dist:2/param:1/repeats:10_median     3700989 ns      3700739 ns           10 bytes/s=270.216M/s ints/s=270.216M/s ns/int=3.70074ns
bench_simditoa_to_chars/dist:2/param:1/repeats:10_stddev        4278 ns         4199 ns           10 bytes/s=306.848k/s ints/s=306.848k/s ns/int=4.1985ps
bench_simditoa_to_chars/dist:2/param:1/repeats:10_cv            0.12 %          0.11 %            10 bytes/s=0.11% ints/s=0.11% ns/int=0.11%
bench_simditoa_to_chars/dist:2/param:1/repeats:10_max        3705782 ns      3705080 ns           10 bytes/s=270.773M/s ints/s=270.773M/s ns/int=3.70508ns
bench_simditoa_to_chars/dist:2/param:4/repeats:10_mean       4437468 ns      4437297 ns           10 bytes/s=901.45M/s ints/s=225.362M/s ns/int=4.4373ns
bench_simditoa_to_chars/dist:2/param:4/repeats:10_median     4436840 ns      4436733 ns           10 bytes/s=901.564M/s ints/s=225.391M/s ns/int=4.43673ns
bench_simditoa_to_chars/dist:2/param:4/repeats:10_stddev        2263 ns         2001 ns           10 bytes/s=406.086k/s ints/s=101.521k/s ns/int=2.0011ps
bench_simditoa_to_chars/dist:2/param:4/repeats:10_cv            0.05 %          0.05 %            10 bytes/s=0.05% ints/s=0.05% ns/int=0.05%
bench_simditoa_to_chars/dist:2/param:4/repeats:10_max        4443825 ns      4442924 ns           10 bytes/s=901.677M/s ints/s=225.419M/s ns/int=4.44292ns
bench_simditoa_to_chars/dist:2/param:8/repeats:10_mean       4438024 ns      4437929 ns           10 bytes/s=1.80264G/s ints/s=225.33M/s ns/int=4.43793ns
bench_simditoa_to_chars/dist:2/param:8/repeats:10_median     4437746 ns      4437672 ns           10 bytes/s=1.80275G/s ints/s=225.343M/s ns/int=4.43767ns
bench_simditoa_to_chars/dist:2/param:8/repeats:10_stddev         931 ns          910 ns           10 bytes/s=369.428k/s ints/s=46.1786k/s ns/int=909.59fs
bench_simditoa_to_chars/dist:2/param:8/repeats:10_cv            0.02 %          0.02 %            10 bytes/s=0.02% ints/s=0.02% ns/int=0.02%
bench_simditoa_to_chars/dist:2/param:8/repeats:10_max        4439555 ns      4439476 ns           10 bytes/s=1.80312G/s ints/s=225.39M/s ns/int=4.43948ns
bench_simditoa_to_chars/dist:2/param:12/repeats:10_mean      5268595 ns      5268482 ns           10 bytes/s=2.2777G/s ints/s=189.808M/s ns/int=5.26848ns
bench_simditoa_to_chars/dist:2/param:12/repeats:10_median    5268941 ns      5268838 ns           10 bytes/s=2.27754G/s ints/s=189.795M/s ns/int=5.26884ns
bench_simditoa_to_chars/dist:2/param:12/repeats:10_stddev       1282 ns         1264 ns           10 bytes/s=546.627k/s ints/s=45.5523k/s ns/int=1.26372ps
bench_simditoa_to_chars/dist:2/param:12/repeats:10_cv           0.02 %          0.02 %            10 bytes/s=0.02% ints/s=0.02% ns/int=0.02%
bench_simditoa_to_chars/dist:2/param:12/repeats:10_max       5269789 ns      5269550 ns           10 bytes/s=2.2792G/s ints/s=189.933M/s ns/int=5.26955ns
bench_simditoa_to_chars/dist:2/param:16/repeats:10_mean      5271698 ns      5271563 ns           10 bytes/s=3.03515G/s ints/s=189.697M/s ns/int=5.27156ns
bench_simditoa_to_chars/dist:2/param:16/repeats:10_median    5270356 ns      5270117 ns           10 bytes/s=3.03599G/s ints/s=189.749M/s ns/int=5.27012ns
bench_simditoa_to_chars/dist:2/param:16/repeats:10_stddev       2591 ns         2588 ns           10 bytes/s=1.48969M/s ints/s=93.1056k/s ns/int=2.58844ps
bench_simditoa_to_chars/dist:2/param:16/repeats:10_cv           0.05 %          0.05 %            10 bytes/s=0.05% ints/s=0.05% ns/int=0.05%
bench_simditoa_to_chars/dist:2/param:16/repeats:10_max       5276889 ns      5276822 ns           10 bytes/s=3.03641G/s ints/s=189.775M/s ns/int=5.27682ns
bench_simditoa_to_chars/dist:2/param:19/repeats:10_mean      5416205 ns      5416081 ns           10 bytes/s=3.50807G/s ints/s=184.635M/s ns/int=5.41608ns
bench_simditoa_to_chars/dist:2/param:19/repeats:10_median    5416426 ns      5416287 ns           10 bytes/s=3.50794G/s ints/s=184.628M/s ns/int=5.41629ns
bench_simditoa_to_chars/dist:2/param:19/repeats:10_stddev       1297 ns         1262 ns           10 bytes/s=817.782k/s ints/s=43.0411k/s ns/int=1.26249ps
bench_simditoa_to_chars/dist:2/param:19/repeats:10_cv           0.02 %          0.02 %            10 bytes/s=0.02% ints/s=0.02% ns/int=0.02%
bench_simditoa_to_chars/dist:2/param:19/repeats:10_max       5418367 ns      5418120 ns           10 bytes/s=3.50947G/s ints/s=184.709M/s ns/int=5.41812ns
bench_null/dist:0/param:0/repeats:10_mean                     370869 ns       370866 ns           10 bytes/s=21.6978G/s ints/s=2.71223G/s ns/int=370.866ps
bench_null/dist:0/param:0/repeats:10_median                   375909 ns       375907 ns           10 bytes/s=21.352G/s ints/s=2.669G/s ns/int=375.907ps
bench_null/dist:0/param:0/repeats:10_stddev                    29809 ns        29808 ns           10 bytes/s=1.75228G/s ints/s=219.035M/s ns/int=29.808ps
bench_null/dist:0/param:0/repeats:10_cv                         8.04 %          8.04 %            10 bytes/s=8.08% ints/s=8.08% ns/int=8.04%
bench_null/dist:0/param:0/repeats:10_max                      401155 ns       401153 ns           10 bytes/s=23.6556G/s ints/s=2.95695G/s ns/int=401.153ps
bench_null/dist:1/param:0/repeats:10_mean                     375179 ns       375175 ns           10 bytes/s=21.4455G/s ints/s=2.68069G/s ns/int=375.175ps
bench_null/dist:1/param:0/repeats:10_median                   395493 ns       395489 ns           10 bytes/s=20.2284G/s ints/s=2.52855G/s ns/int=395.489ps
bench_null/dist:1/param:0/repeats:10_stddev                    29393 ns        29394 ns           10 bytes/s=1.73197G/s ints/s=216.496M/s ns/int=29.3938ps
bench_null/dist:1/param:0/repeats:10_cv                         7.83 %          7.83 %            10 bytes/s=8.08% ints/s=8.08% ns/int=7.83%
bench_null/dist:1/param:0/repeats:10_max                      400846 ns       400838 ns           10 bytes/s=23.5878G/s ints/s=2.94847G/s ns/int=400.838ps
bench_null/dist:2/param:1/repeats:10_mean                     394350 ns       394347 ns           10 bytes/s=20.2888G/s ints/s=2.5361G/s ns/int=394.347ps
bench_null/dist:2/param:1/repeats:10_median                   394580 ns       394573 ns           10 bytes/s=20.2752G/s ints/s=2.5344G/s ns/int=394.573ps
bench_null/dist:2/param:1/repeats:10_stddev                     4169 ns         4169 ns           10 bytes/s=214.507M/s ints/s=26.8134M/s ns/int=4.16864ps
bench_null/dist:2/param:1/repeats:10_cv                         1.06 %          1.06 %            10 bytes/s=1.06% ints/s=1.06% ns/int=1.06%
bench_null/dist:2/param:1/repeats:10_max                      402090 ns       402087 ns           10 bytes/s=20.682G/s ints/s=2.58524G/s ns/int=402.087ps
bench_null/dist:2/param:4/repeats:10_mean                     389833 ns       389828 ns           10 bytes/s=20.525G/s ints/s=2.56563G/s ns/int=389.828ps
bench_null/dist:2/param:4/repeats:10_median                   388466 ns       388460 ns           10 bytes/s=20.5941G/s ints/s=2.57427G/s ns/int=388.46ps
bench_null/dist:2/param:4/repeats:10_stddev                     5103 ns         5102 ns           10 bytes/s=269.171M/s ints/s=33.6464M/s ns/int=5.1021ps
bench_null/dist:2/param:4/repeats:10_cv                         1.31 %          1.31 %            10 bytes/s=1.31% ints/s=1.31% ns/int=1.31%
bench_null/dist:2/param:4/repeats:10_max                      398271 ns       398263 ns           10 bytes/s=21.0559G/s ints/s=2.63198G/s ns/int=398.263ps
bench_null/dist:2/param:8/repeats:10_mean                     375948 ns       375943 ns           10 bytes/s=21.3305G/s ints/s=2.66631G/s ns/int=375.943ps
bench_null/dist:2/param:8/repeats:10_median                   382362 ns       382354 ns           10 bytes/s=20.9235G/s ints/s=2.61544G/s ns/int=382.354ps
bench_null/dist:2/param:8/repeats:10_stddev                    18787 ns        18787 ns           10 bytes/s=1.12847G/s ints/s=141.058M/s ns/int=18.7868ps
bench_null/dist:2/param:8/repeats:10_cv                         5.00 %          5.00 %            10 bytes/s=5.29% ints/s=5.29% ns/int=5.00%
bench_null/dist:2/param:8/repeats:10_max                      393442 ns       393436 ns           10 bytes/s=23.7327G/s ints/s=2.96658G/s ns/int=393.436ps
bench_null/dist:2/param:12/repeats:10_mean                    341652 ns       341649 ns           10 bytes/s=23.4469G/s ints/s=2.93086G/s ns/int=341.649ps
bench_null/dist:2/param:12/repeats:10_median                  337060 ns       337058 ns           10 bytes/s=23.7348G/s ints/s=2.96685G/s ns/int=337.058ps
bench_null/dist:2/param:12/repeats:10_stddev                   13752 ns        13751 ns           10 bytes/s=856.894M/s ints/s=107.112M/s ns/int=13.7511ps
bench_null/dist:2/param:12/repeats:10_cv                        4.03 %          4.02 %            10 bytes/s=3.65% ints/s=3.65% ns/int=4.02%
bench_null/dist:2/param:12/repeats:10_max                     380744 ns       380739 ns           10 bytes/s=23.7497G/s ints/s=2.96871G/s ns/int=380.739ps
bench_null/dist:2/param:16/repeats:10_mean                    337300 ns       337296 ns           10 bytes/s=23.718G/s ints/s=2.96475G/s ns/int=337.296ps
bench_null/dist:2/param:16/repeats:10_median                  337201 ns       337198 ns           10 bytes/s=23.7249G/s ints/s=2.96561G/s ns/int=337.198ps
bench_null/dist:2/param:16/repeats:10_stddev                     235 ns          234 ns           10 bytes/s=16.4579M/s ints/s=2.05724M/s ns/int=234.385fs
bench_null/dist:2/param:16/repeats:10_cv                        0.07 %          0.07 %            10 bytes/s=0.07% ints/s=0.07% ns/int=0.07%
bench_null/dist:2/param:16/repeats:10_max                     337932 ns       337926 ns           10 bytes/s=23.729G/s ints/s=2.96612G/s ns/int=337.926ps
bench_null/dist:2/param:19/repeats:10_mean                    366190 ns       366187 ns           10 bytes/s=21.9636G/s ints/s=2.74546G/s ns/int=366.187ps
bench_null/dist:2/param:19/repeats:10_median                  367904 ns       367900 ns           10 bytes/s=21.8073G/s ints/s=2.72592G/s ns/int=367.9ps
bench_null/dist:2/param:19/repeats:10_stddev                   28142 ns        28142 ns           10 bytes/s=1.69045G/s ints/s=211.306M/s ns/int=28.1416ps
bench_null/dist:2/param:19/repeats:10_cv                        7.69 %          7.69 %            10 bytes/s=7.70% ints/s=7.70% ns/int=7.69%
bench_null/dist:2/param:19/repeats:10_max                     396836 ns       396826 ns           10 bytes/s=23.7073G/s ints/s=2.96341G/s ns/int=396.826ps
bench_std_to_chars/dist:0/param:0/repeats:10_mean           23806655 ns     23806285 ns           10 bytes/s=814.013M/s ints/s=42.0057M/s ns/int=23.8063ns
bench_std_to_chars/dist:0/param:0/repeats:10_median         23802440 ns     23802056 ns           10 bytes/s=814.157M/s ints/s=42.0132M/s ns/int=23.8021ns
bench_std_to_chars/dist:0/param:0/repeats:10_stddev            16158 ns        16048 ns           10 bytes/s=548.509k/s ints/s=28.3049k/s ns/int=16.0475ps
bench_std_to_chars/dist:0/param:0/repeats:10_cv                 0.07 %          0.07 %            10 bytes/s=0.07% ints/s=0.07% ns/int=0.07%
bench_std_to_chars/dist:0/param:0/repeats:10_max            23838120 ns     23837060 ns           10 bytes/s=814.682M/s ints/s=42.0403M/s ns/int=23.8371ns
bench_std_to_chars/dist:1/param:0/repeats:10_mean           22744361 ns     22743892 ns           10 bytes/s=442.059M/s ints/s=43.968M/s ns/int=22.7439ns
bench_std_to_chars/dist:1/param:0/repeats:10_median         22731493 ns     22731019 ns           10 bytes/s=442.308M/s ints/s=43.9927M/s ns/int=22.731ns
bench_std_to_chars/dist:1/param:0/repeats:10_stddev            44274 ns        44183 ns           10 bytes/s=856.135k/s ints/s=85.1528k/s ns/int=44.1832ps
bench_std_to_chars/dist:1/param:0/repeats:10_cv                 0.19 %          0.19 %            10 bytes/s=0.19% ints/s=0.19% ns/int=0.19%
bench_std_to_chars/dist:1/param:0/repeats:10_max            22851568 ns     22851023 ns           10 bytes/s=442.705M/s ints/s=44.0323M/s ns/int=22.851ns
bench_std_to_chars/dist:2/param:1/repeats:10_mean            2849078 ns      2849025 ns           10 bytes/s=350.997M/s ints/s=350.997M/s ns/int=2.84902ns
bench_std_to_chars/dist:2/param:1/repeats:10_median          2849431 ns      2849376 ns           10 bytes/s=350.954M/s ints/s=350.954M/s ns/int=2.84938ns
bench_std_to_chars/dist:2/param:1/repeats:10_stddev             1497 ns         1499 ns           10 bytes/s=184.676k/s ints/s=184.676k/s ns/int=1.49877ps
bench_std_to_chars/dist:2/param:1/repeats:10_cv                 0.05 %          0.05 %            10 bytes/s=0.05% ints/s=0.05% ns/int=0.05%
bench_std_to_chars/dist:2/param:1/repeats:10_max             2851253 ns      2851259 ns           10 bytes/s=351.314M/s ints/s=351.314M/s ns/int=2.85126ns
bench_std_to_chars/dist:2/param:4/repeats:10_mean            3074845 ns      3074784 ns           10 bytes/s=1.30091G/s ints/s=325.227M/s ns/int=3.07478ns
bench_std_to_chars/dist:2/param:4/repeats:10_median          3074113 ns      3074015 ns           10 bytes/s=1.30123G/s ints/s=325.307M/s ns/int=3.07401ns
bench_std_to_chars/dist:2/param:4/repeats:10_stddev             4774 ns         4781 ns           10 bytes/s=2.01893M/s ints/s=504.732k/s ns/int=4.78082ps
bench_std_to_chars/dist:2/param:4/repeats:10_cv                 0.16 %          0.16 %            10 bytes/s=0.16% ints/s=0.16% ns/int=0.16%
bench_std_to_chars/dist:2/param:4/repeats:10_max             3086237 ns      3086159 ns           10 bytes/s=1.30331G/s ints/s=325.828M/s ns/int=3.08616ns
bench_std_to_chars/dist:2/param:8/repeats:10_mean            6845374 ns      6845271 ns           10 bytes/s=1.16869G/s ints/s=146.086M/s ns/int=6.84527ns
bench_std_to_chars/dist:2/param:8/repeats:10_median          6843550 ns      6843485 ns           10 bytes/s=1.169G/s ints/s=146.124M/s ns/int=6.84348ns
bench_std_to_chars/dist:2/param:8/repeats:10_stddev             8989 ns         8986 ns           10 bytes/s=1.53294M/s ints/s=191.618k/s ns/int=8.98634ps
bench_std_to_chars/dist:2/param:8/repeats:10_cv                 0.13 %          0.13 %            10 bytes/s=0.13% ints/s=0.13% ns/int=0.13%
bench_std_to_chars/dist:2/param:8/repeats:10_max             6863185 ns      6863031 ns           10 bytes/s=1.17063G/s ints/s=146.329M/s ns/int=6.86303ns
bench_std_to_chars/dist:2/param:12/repeats:10_mean          10448744 ns     10448590 ns           10 bytes/s=1.14849G/s ints/s=95.7072M/s ns/int=10.4486ns
bench_std_to_chars/dist:2/param:12/repeats:10_median        10450962 ns     10450810 ns           10 bytes/s=1.14824G/s ints/s=95.6864M/s ns/int=10.4508ns
bench_std_to_chars/dist:2/param:12/repeats:10_stddev           24329 ns        24360 ns           10 bytes/s=2.68002M/s ints/s=223.335k/s ns/int=24.3602ps
bench_std_to_chars/dist:2/param:12/repeats:10_cv                0.23 %          0.23 %            10 bytes/s=0.23% ints/s=0.23% ns/int=0.23%
bench_std_to_chars/dist:2/param:12/repeats:10_max           10485623 ns     10485639 ns           10 bytes/s=1.15338G/s ints/s=96.1154M/s ns/int=10.4856ns
bench_std_to_chars/dist:2/param:16/repeats:10_mean          13980778 ns     13980571 ns           10 bytes/s=1.14445G/s ints/s=71.5279M/s ns/int=13.9806ns
bench_std_to_chars/dist:2/param:16/repeats:10_median        13987208 ns     13987071 ns           10 bytes/s=1.14391G/s ints/s=71.4946M/s ns/int=13.9871ns
bench_std_to_chars/dist:2/param:16/repeats:10_stddev           14984 ns        15058 ns           10 bytes/s=1.23337M/s ints/s=77.0859k/s ns/int=15.0584ps
bench_std_to_chars/dist:2/param:16/repeats:10_cv                0.11 %          0.11 %            10 bytes/s=0.11% ints/s=0.11% ns/int=0.11%
bench_std_to_chars/dist:2/param:16/repeats:10_max           14000286 ns     14000308 ns           10 bytes/s=1.14661G/s ints/s=71.6628M/s ns/int=14.0003ns
bench_std_to_chars/dist:2/param:19/repeats:10_mean          17676364 ns     17676055 ns           10 bytes/s=1.0749G/s ints/s=56.5738M/s ns/int=17.6761ns
bench_std_to_chars/dist:2/param:19/repeats:10_median        17673342 ns     17673145 ns           10 bytes/s=1.07508G/s ints/s=56.583M/s ns/int=17.6731ns
bench_std_to_chars/dist:2/param:19/repeats:10_stddev           19897 ns        19811 ns           10 bytes/s=1.20459M/s ints/s=63.3995k/s ns/int=19.8107ps
bench_std_to_chars/dist:2/param:19/repeats:10_cv                0.11 %          0.11 %            10 bytes/s=0.11% ints/s=0.11% ns/int=0.11%
bench_std_to_chars/dist:2/param:19/repeats:10_max           17701435 ns     17701475 ns           10 bytes/s=1.07642G/s ints/s=56.6538M/s ns/int=17.7015ns
bench_yy_itoa/dist:0/param:0/repeats:10_mean                 7773970 ns      7773862 ns           10 bytes/s=2.49279G/s ints/s=128.636M/s ns/int=7.77386ns
bench_yy_itoa/dist:0/param:0/repeats:10_median               7772412 ns      7772376 ns           10 bytes/s=2.49327G/s ints/s=128.661M/s ns/int=7.77238ns
bench_yy_itoa/dist:0/param:0/repeats:10_stddev                  5030 ns         5001 ns           10 bytes/s=1.6012M/s ints/s=82.6274k/s ns/int=5.00076ps
bench_yy_itoa/dist:0/param:0/repeats:10_cv                      0.06 %          0.06 %            10 bytes/s=0.06% ints/s=0.06% ns/int=0.06%
bench_yy_itoa/dist:0/param:0/repeats:10_max                  7787878 ns      7787712 ns           10 bytes/s=2.49375G/s ints/s=128.686M/s ns/int=7.78771ns
bench_yy_itoa/dist:1/param:0/repeats:10_mean                14882435 ns     14882079 ns           10 bytes/s=675.587M/s ints/s=67.1951M/s ns/int=14.8821ns
bench_yy_itoa/dist:1/param:0/repeats:10_median              14875049 ns     14874823 ns           10 bytes/s=675.914M/s ints/s=67.2277M/s ns/int=14.8748ns
bench_yy_itoa/dist:1/param:0/repeats:10_stddev                 26309 ns        26296 ns           10 bytes/s=1.19286M/s ints/s=118.644k/s ns/int=26.2962ps
bench_yy_itoa/dist:1/param:0/repeats:10_cv                      0.18 %          0.18 %            10 bytes/s=0.18% ints/s=0.18% ns/int=0.18%
bench_yy_itoa/dist:1/param:0/repeats:10_max                 14920013 ns     14919631 ns           10 bytes/s=676.887M/s ints/s=67.3244M/s ns/int=14.9196ns
bench_yy_itoa/dist:2/param:1/repeats:10_mean                 1823763 ns      1823733 ns           10 bytes/s=548.328M/s ints/s=548.328M/s ns/int=1.82373ns
bench_yy_itoa/dist:2/param:1/repeats:10_median               1823070 ns      1823038 ns           10 bytes/s=548.535M/s ints/s=548.535M/s ns/int=1.82304ns
bench_yy_itoa/dist:2/param:1/repeats:10_stddev                  3955 ns         3967 ns           10 bytes/s=1.18959M/s ints/s=1.18959M/s ns/int=3.96713ps
bench_yy_itoa/dist:2/param:1/repeats:10_cv                      0.22 %          0.22 %            10 bytes/s=0.22% ints/s=0.22% ns/int=0.22%
bench_yy_itoa/dist:2/param:1/repeats:10_max                  1833008 ns      1832993 ns           10 bytes/s=549.614M/s ints/s=549.614M/s ns/int=1.83299ns
bench_yy_itoa/dist:2/param:4/repeats:10_mean                 2368175 ns      2368144 ns           10 bytes/s=1.68909G/s ints/s=422.272M/s ns/int=2.36814ns
bench_yy_itoa/dist:2/param:4/repeats:10_median               2367985 ns      2367930 ns           10 bytes/s=1.68924G/s ints/s=422.31M/s ns/int=2.36793ns
bench_yy_itoa/dist:2/param:4/repeats:10_stddev                  1034 ns         1029 ns           10 bytes/s=733.802k/s ints/s=183.451k/s ns/int=1.02924ps
bench_yy_itoa/dist:2/param:4/repeats:10_cv                      0.04 %          0.04 %            10 bytes/s=0.04% ints/s=0.04% ns/int=0.04%
bench_yy_itoa/dist:2/param:4/repeats:10_max                  2370404 ns      2370346 ns           10 bytes/s=1.6899G/s ints/s=422.475M/s ns/int=2.37035ns
bench_yy_itoa/dist:2/param:8/repeats:10_mean                 3349704 ns      3349634 ns           10 bytes/s=2.38834G/s ints/s=298.543M/s ns/int=3.34963ns
bench_yy_itoa/dist:2/param:8/repeats:10_median               3349775 ns      3349714 ns           10 bytes/s=2.38827G/s ints/s=298.534M/s ns/int=3.34971ns
bench_yy_itoa/dist:2/param:8/repeats:10_stddev                 10101 ns        10088 ns           10 bytes/s=7.19362M/s ints/s=899.202k/s ns/int=10.0881ps
bench_yy_itoa/dist:2/param:8/repeats:10_cv                      0.30 %          0.30 %            10 bytes/s=0.30% ints/s=0.30% ns/int=0.30%
bench_yy_itoa/dist:2/param:8/repeats:10_max                  3363243 ns      3363087 ns           10 bytes/s=2.39867G/s ints/s=299.834M/s ns/int=3.36309ns
bench_yy_itoa/dist:2/param:12/repeats:10_mean                4864906 ns      4864827 ns           10 bytes/s=2.46669G/s ints/s=205.557M/s ns/int=4.86483ns
bench_yy_itoa/dist:2/param:12/repeats:10_median              4865225 ns      4865191 ns           10 bytes/s=2.4665G/s ints/s=205.542M/s ns/int=4.86519ns
bench_yy_itoa/dist:2/param:12/repeats:10_stddev                 5453 ns         5450 ns           10 bytes/s=2.76326M/s ints/s=230.272k/s ns/int=5.44957ps
bench_yy_itoa/dist:2/param:12/repeats:10_cv                     0.11 %          0.11 %            10 bytes/s=0.11% ints/s=0.11% ns/int=0.11%
bench_yy_itoa/dist:2/param:12/repeats:10_max                 4872259 ns      4872218 ns           10 bytes/s=2.47012G/s ints/s=205.843M/s ns/int=4.87222ns
bench_yy_itoa/dist:2/param:16/repeats:10_mean                5899046 ns      5898949 ns           10 bytes/s=2.71235G/s ints/s=169.522M/s ns/int=5.89895ns
bench_yy_itoa/dist:2/param:16/repeats:10_median              5898098 ns      5897980 ns           10 bytes/s=2.71279G/s ints/s=169.55M/s ns/int=5.89798ns
bench_yy_itoa/dist:2/param:16/repeats:10_stddev                 3124 ns         3155 ns           10 bytes/s=1.45053M/s ints/s=90.6581k/s ns/int=3.15548ps
bench_yy_itoa/dist:2/param:16/repeats:10_cv                     0.05 %          0.05 %            10 bytes/s=0.05% ints/s=0.05% ns/int=0.05%
bench_yy_itoa/dist:2/param:16/repeats:10_max                 5903724 ns      5903585 ns           10 bytes/s=2.71374G/s ints/s=169.609M/s ns/int=5.90358ns
bench_yy_itoa/dist:2/param:19/repeats:10_mean                7155818 ns      7155724 ns           10 bytes/s=2.65522G/s ints/s=139.748M/s ns/int=7.15572ns
bench_yy_itoa/dist:2/param:19/repeats:10_median              7155739 ns      7155582 ns           10 bytes/s=2.65527G/s ints/s=139.751M/s ns/int=7.15558ns
bench_yy_itoa/dist:2/param:19/repeats:10_stddev                 3012 ns         3032 ns           10 bytes/s=1.12507M/s ints/s=59.2141k/s ns/int=3.03194ps
bench_yy_itoa/dist:2/param:19/repeats:10_cv                     0.04 %          0.04 %            10 bytes/s=0.04% ints/s=0.04% ns/int=0.04%
bench_yy_itoa/dist:2/param:19/repeats:10_max                 7160473 ns      7160491 ns           10 bytes/s=2.65712G/s ints/s=139.848M/s ns/int=7.16049ns
bench_jeaiii_itoa/dist:0/param:0/repeats:10_mean            13387613 ns     13387389 ns           10 bytes/s=1.44755G/s ints/s=74.6984M/s ns/int=13.3874ns
bench_jeaiii_itoa/dist:0/param:0/repeats:10_median          13391931 ns     13391704 ns           10 bytes/s=1.44706G/s ints/s=74.6731M/s ns/int=13.3917ns
bench_jeaiii_itoa/dist:0/param:0/repeats:10_stddev             58434 ns        58444 ns           10 bytes/s=6.30291M/s ints/s=325.251k/s ns/int=58.4444ps
bench_jeaiii_itoa/dist:0/param:0/repeats:10_cv                  0.44 %          0.44 %            10 bytes/s=0.44% ints/s=0.44% ns/int=0.44%
bench_jeaiii_itoa/dist:0/param:0/repeats:10_max             13514292 ns     13514028 ns           10 bytes/s=1.45665G/s ints/s=75.168M/s ns/int=13.514ns
bench_jeaiii_itoa/dist:1/param:0/repeats:10_mean            17821996 ns     17821562 ns           10 bytes/s=564.154M/s ints/s=56.1118M/s ns/int=17.8216ns
bench_jeaiii_itoa/dist:1/param:0/repeats:10_median          17824212 ns     17823488 ns           10 bytes/s=564.093M/s ints/s=56.1057M/s ns/int=17.8235ns
bench_jeaiii_itoa/dist:1/param:0/repeats:10_stddev             15349 ns        15482 ns           10 bytes/s=490.289k/s ints/s=48.7651k/s ns/int=15.4822ps
bench_jeaiii_itoa/dist:1/param:0/repeats:10_cv                  0.09 %          0.09 %            10 bytes/s=0.09% ints/s=0.09% ns/int=0.09%
bench_jeaiii_itoa/dist:1/param:0/repeats:10_max             17842646 ns     17842690 ns           10 bytes/s=565.032M/s ints/s=56.1991M/s ns/int=17.8427ns
bench_jeaiii_itoa/dist:2/param:1/repeats:10_mean             1343630 ns      1343605 ns           10 bytes/s=744.322M/s ints/s=744.322M/s ns/int=1.3436ns
bench_jeaiii_itoa/dist:2/param:1/repeats:10_median           1348623 ns      1348589 ns           10 bytes/s=741.516M/s ints/s=741.516M/s ns/int=1.34859ns
bench_jeaiii_itoa/dist:2/param:1/repeats:10_stddev             12099 ns        12107 ns           10 bytes/s=6.82335M/s ints/s=6.82335M/s ns/int=12.1071ps
bench_jeaiii_itoa/dist:2/param:1/repeats:10_cv                  0.90 %          0.90 %            10 bytes/s=0.92% ints/s=0.92% ns/int=0.90%
bench_jeaiii_itoa/dist:2/param:1/repeats:10_max              1351583 ns      1351533 ns           10 bytes/s=762.044M/s ints/s=762.044M/s ns/int=1.35153ns
bench_jeaiii_itoa/dist:2/param:4/repeats:10_mean             1697083 ns      1697057 ns           10 bytes/s=2.35702G/s ints/s=589.255M/s ns/int=1.69706ns
bench_jeaiii_itoa/dist:2/param:4/repeats:10_median           1697053 ns      1697024 ns           10 bytes/s=2.35707G/s ints/s=589.267M/s ns/int=1.69702ns
bench_jeaiii_itoa/dist:2/param:4/repeats:10_stddev               210 ns          201 ns           10 bytes/s=279.586k/s ints/s=69.8966k/s ns/int=201.302fs
bench_jeaiii_itoa/dist:2/param:4/repeats:10_cv                  0.01 %          0.01 %            10 bytes/s=0.01% ints/s=0.01% ns/int=0.01%
bench_jeaiii_itoa/dist:2/param:4/repeats:10_max              1697413 ns      1697376 ns           10 bytes/s=2.35753G/s ints/s=589.383M/s ns/int=1.69738ns
bench_jeaiii_itoa/dist:2/param:8/repeats:10_mean             2916503 ns      2916459 ns           10 bytes/s=2.74306G/s ints/s=342.882M/s ns/int=2.91646ns
bench_jeaiii_itoa/dist:2/param:8/repeats:10_median           2915108 ns      2915081 ns           10 bytes/s=2.74435G/s ints/s=343.044M/s ns/int=2.91508ns
bench_jeaiii_itoa/dist:2/param:8/repeats:10_stddev              4129 ns         4128 ns           10 bytes/s=3.88168M/s ints/s=485.21k/s ns/int=4.12796ps
bench_jeaiii_itoa/dist:2/param:8/repeats:10_cv                  0.14 %          0.14 %            10 bytes/s=0.14% ints/s=0.14% ns/int=0.14%
bench_jeaiii_itoa/dist:2/param:8/repeats:10_max              2922807 ns      2922778 ns           10 bytes/s=2.74845G/s ints/s=343.556M/s ns/int=2.92278ns
bench_jeaiii_itoa/dist:2/param:12/repeats:10_mean            4934524 ns      4934437 ns           10 bytes/s=2.43189G/s ints/s=202.657M/s ns/int=4.93444ns
bench_jeaiii_itoa/dist:2/param:12/repeats:10_median          4935305 ns      4935252 ns           10 bytes/s=2.43149G/s ints/s=202.624M/s ns/int=4.93525ns
bench_jeaiii_itoa/dist:2/param:12/repeats:10_stddev             3222 ns         3275 ns           10 bytes/s=1.61439M/s ints/s=134.532k/s ns/int=3.27488ps
bench_jeaiii_itoa/dist:2/param:12/repeats:10_cv                 0.07 %          0.07 %            10 bytes/s=0.07% ints/s=0.07% ns/int=0.07%
bench_jeaiii_itoa/dist:2/param:12/repeats:10_max             4938783 ns      4938795 ns           10 bytes/s=2.43456G/s ints/s=202.88M/s ns/int=4.93879ns
bench_jeaiii_itoa/dist:2/param:16/repeats:10_mean            5990972 ns      5990888 ns           10 bytes/s=2.67073G/s ints/s=166.921M/s ns/int=5.99089ns
bench_jeaiii_itoa/dist:2/param:16/repeats:10_median          5990732 ns      5990646 ns           10 bytes/s=2.67083G/s ints/s=166.927M/s ns/int=5.99065ns
bench_jeaiii_itoa/dist:2/param:16/repeats:10_stddev             9687 ns         9645 ns           10 bytes/s=4.30935M/s ints/s=269.335k/s ns/int=9.64461ps
bench_jeaiii_itoa/dist:2/param:16/repeats:10_cv                 0.16 %          0.16 %            10 bytes/s=0.16% ints/s=0.16% ns/int=0.16%
bench_jeaiii_itoa/dist:2/param:16/repeats:10_max             6000058 ns      5999863 ns           10 bytes/s=2.68135G/s ints/s=167.584M/s ns/int=5.99986ns
bench_jeaiii_itoa/dist:2/param:19/repeats:10_mean            7831253 ns      7831118 ns           10 bytes/s=2.42625G/s ints/s=127.697M/s ns/int=7.83112ns
bench_jeaiii_itoa/dist:2/param:19/repeats:10_median          7818887 ns      7818514 ns           10 bytes/s=2.43013G/s ints/s=127.902M/s ns/int=7.81851ns
bench_jeaiii_itoa/dist:2/param:19/repeats:10_stddev            30217 ns        30206 ns           10 bytes/s=9.33267M/s ints/s=491.193k/s ns/int=30.2065ps
bench_jeaiii_itoa/dist:2/param:19/repeats:10_cv                 0.39 %          0.39 %            10 bytes/s=0.38% ints/s=0.38% ns/int=0.39%
bench_jeaiii_itoa/dist:2/param:19/repeats:10_max             7892363 ns      7892203 ns           10 bytes/s=2.43724G/s ints/s=128.276M/s ns/int=7.8922ns
bench_tencent_rapidjson/dist:0/param:0/repeats:10_mean      16179467 ns     16179168 ns           10 bytes/s=1.19775G/s ints/s=61.8079M/s ns/int=16.1792ns
bench_tencent_rapidjson/dist:0/param:0/repeats:10_median    16177961 ns     16177879 ns           10 bytes/s=1.19785G/s ints/s=61.8128M/s ns/int=16.1779ns
bench_tencent_rapidjson/dist:0/param:0/repeats:10_stddev        5687 ns         5661 ns           10 bytes/s=418.995k/s ints/s=21.6215k/s ns/int=5.66142ps
bench_tencent_rapidjson/dist:0/param:0/repeats:10_cv            0.04 %          0.03 %            10 bytes/s=0.03% ints/s=0.03% ns/int=0.03%
bench_tencent_rapidjson/dist:0/param:0/repeats:10_max       16191332 ns     16191150 ns           10 bytes/s=1.19826G/s ints/s=61.8344M/s ns/int=16.1912ns
bench_tencent_rapidjson/dist:1/param:0/repeats:10_mean      21852963 ns     21852403 ns           10 bytes/s=460.092M/s ints/s=45.7616M/s ns/int=21.8524ns
bench_tencent_rapidjson/dist:1/param:0/repeats:10_median    21848959 ns     21848562 ns           10 bytes/s=460.172M/s ints/s=45.7696M/s ns/int=21.8486ns
bench_tencent_rapidjson/dist:1/param:0/repeats:10_stddev       18212 ns        18385 ns           10 bytes/s=386.956k/s ints/s=38.4874k/s ns/int=18.3847ps
bench_tencent_rapidjson/dist:1/param:0/repeats:10_cv            0.08 %          0.08 %            10 bytes/s=0.08% ints/s=0.08% ns/int=0.08%
bench_tencent_rapidjson/dist:1/param:0/repeats:10_max       21879208 ns     21878775 ns           10 bytes/s=460.51M/s ints/s=45.8032M/s ns/int=21.8788ns
bench_tencent_rapidjson/dist:2/param:1/repeats:10_mean       2035802 ns      2035762 ns           10 bytes/s=491.407M/s ints/s=491.407M/s ns/int=2.03576ns
bench_tencent_rapidjson/dist:2/param:1/repeats:10_median     2021803 ns      2021756 ns           10 bytes/s=494.62M/s ints/s=494.62M/s ns/int=2.02176ns
bench_tencent_rapidjson/dist:2/param:1/repeats:10_stddev       43206 ns        43197 ns           10 bytes/s=9.99485M/s ints/s=9.99485M/s ns/int=43.1968ps
bench_tencent_rapidjson/dist:2/param:1/repeats:10_cv            2.12 %          2.12 %            10 bytes/s=2.03% ints/s=2.03% ns/int=2.12%
bench_tencent_rapidjson/dist:2/param:1/repeats:10_max        2151171 ns      2151095 ns           10 bytes/s=498.675M/s ints/s=498.675M/s ns/int=2.15109ns
bench_tencent_rapidjson/dist:2/param:4/repeats:10_mean       1958509 ns      1958480 ns           10 bytes/s=2.04242G/s ints/s=510.604M/s ns/int=1.95848ns
bench_tencent_rapidjson/dist:2/param:4/repeats:10_median     1959001 ns      1958971 ns           10 bytes/s=2.04189G/s ints/s=510.472M/s ns/int=1.95897ns
bench_tencent_rapidjson/dist:2/param:4/repeats:10_stddev        5609 ns         5615 ns           10 bytes/s=5.85776M/s ints/s=1.46444M/s ns/int=5.61473ps
bench_tencent_rapidjson/dist:2/param:4/repeats:10_cv            0.29 %          0.29 %            10 bytes/s=0.29% ints/s=0.29% ns/int=0.29%
bench_tencent_rapidjson/dist:2/param:4/repeats:10_max        1969555 ns      1969539 ns           10 bytes/s=2.05443G/s ints/s=513.607M/s ns/int=1.96954ns
bench_tencent_rapidjson/dist:2/param:8/repeats:10_mean       3432034 ns      3431986 ns           10 bytes/s=2.33101G/s ints/s=291.376M/s ns/int=3.43199ns
bench_tencent_rapidjson/dist:2/param:8/repeats:10_median     3431910 ns      3431886 ns           10 bytes/s=2.33108G/s ints/s=291.385M/s ns/int=3.43189ns
bench_tencent_rapidjson/dist:2/param:8/repeats:10_stddev         903 ns          887 ns           10 bytes/s=602.418k/s ints/s=75.3022k/s ns/int=886.814fs
bench_tencent_rapidjson/dist:2/param:8/repeats:10_cv            0.03 %          0.03 %            10 bytes/s=0.03% ints/s=0.03% ns/int=0.03%
bench_tencent_rapidjson/dist:2/param:8/repeats:10_max        3433215 ns      3433128 ns           10 bytes/s=2.33227G/s ints/s=291.534M/s ns/int=3.43313ns
bench_tencent_rapidjson/dist:2/param:12/repeats:10_mean      8037643 ns      8037544 ns           10 bytes/s=1.49299G/s ints/s=124.416M/s ns/int=8.03754ns
bench_tencent_rapidjson/dist:2/param:12/repeats:10_median    8038972 ns      8038855 ns           10 bytes/s=1.49275G/s ints/s=124.396M/s ns/int=8.03885ns
bench_tencent_rapidjson/dist:2/param:12/repeats:10_stddev       4034 ns         4077 ns           10 bytes/s=757.364k/s ints/s=63.1137k/s ns/int=4.07678ps
bench_tencent_rapidjson/dist:2/param:12/repeats:10_cv           0.05 %          0.05 %            10 bytes/s=0.05% ints/s=0.05% ns/int=0.05%
bench_tencent_rapidjson/dist:2/param:12/repeats:10_max       8043090 ns      8043017 ns           10 bytes/s=1.4941G/s ints/s=124.508M/s ns/int=8.04302ns
bench_tencent_rapidjson/dist:2/param:16/repeats:10_mean      8043549 ns      8043391 ns           10 bytes/s=1.98921G/s ints/s=124.326M/s ns/int=8.04339ns
bench_tencent_rapidjson/dist:2/param:16/repeats:10_median    8042870 ns      8042795 ns           10 bytes/s=1.98936G/s ints/s=124.335M/s ns/int=8.04279ns
bench_tencent_rapidjson/dist:2/param:16/repeats:10_stddev       2596 ns         2619 ns           10 bytes/s=647.401k/s ints/s=40.4625k/s ns/int=2.61873ps
bench_tencent_rapidjson/dist:2/param:16/repeats:10_cv           0.03 %          0.03 %            10 bytes/s=0.03% ints/s=0.03% ns/int=0.03%
bench_tencent_rapidjson/dist:2/param:16/repeats:10_max       8049573 ns      8049518 ns           10 bytes/s=1.99005G/s ints/s=124.378M/s ns/int=8.04952ns
bench_tencent_rapidjson/dist:2/param:19/repeats:10_mean     12928036 ns     12927835 ns           10 bytes/s=1.4697G/s ints/s=77.3525M/s ns/int=12.9278ns
bench_tencent_rapidjson/dist:2/param:19/repeats:10_median   12926463 ns     12926376 ns           10 bytes/s=1.46986G/s ints/s=77.3612M/s ns/int=12.9264ns
bench_tencent_rapidjson/dist:2/param:19/repeats:10_stddev       5142 ns         5090 ns           10 bytes/s=578.556k/s ints/s=30.4503k/s ns/int=5.09019ps
bench_tencent_rapidjson/dist:2/param:19/repeats:10_cv           0.04 %          0.04 %            10 bytes/s=0.04% ints/s=0.04% ns/int=0.04%
bench_tencent_rapidjson/dist:2/param:19/repeats:10_max      12938271 ns     12937747 ns           10 bytes/s=1.47051G/s ints/s=77.3953M/s ns/int=12.9377ns
bench_fmtlib_fmt/dist:0/param:0/repeats:10_mean             16970707 ns     16970370 ns           10 bytes/s=1.14192G/s ints/s=58.9266M/s ns/int=16.9704ns
bench_fmtlib_fmt/dist:0/param:0/repeats:10_median           16984613 ns     16984089 ns           10 bytes/s=1.14099G/s ints/s=58.8787M/s ns/int=16.9841ns
bench_fmtlib_fmt/dist:0/param:0/repeats:10_stddev              45308 ns        45275 ns           10 bytes/s=3.04779M/s ints/s=157.276k/s ns/int=45.2752ps
bench_fmtlib_fmt/dist:0/param:0/repeats:10_cv                   0.27 %          0.27 %            10 bytes/s=0.27% ints/s=0.27% ns/int=0.27%
bench_fmtlib_fmt/dist:0/param:0/repeats:10_max              17030400 ns     17030222 ns           10 bytes/s=1.14627G/s ints/s=59.1512M/s ns/int=17.0302ns
bench_fmtlib_fmt/dist:1/param:0/repeats:10_mean             22182844 ns     22182390 ns           10 bytes/s=453.247M/s ints/s=45.0808M/s ns/int=22.1824ns
bench_fmtlib_fmt/dist:1/param:0/repeats:10_median           22180527 ns     22179968 ns           10 bytes/s=453.297M/s ints/s=45.0857M/s ns/int=22.18ns
bench_fmtlib_fmt/dist:1/param:0/repeats:10_stddev              12387 ns        12464 ns           10 bytes/s=254.631k/s ints/s=25.3261k/s ns/int=12.4641ps
bench_fmtlib_fmt/dist:1/param:0/repeats:10_cv                   0.06 %          0.06 %            10 bytes/s=0.06% ints/s=0.06% ns/int=0.06%
bench_fmtlib_fmt/dist:1/param:0/repeats:10_max              22203860 ns     22203557 ns           10 bytes/s=453.556M/s ints/s=45.1115M/s ns/int=22.2036ns
bench_fmtlib_fmt/dist:2/param:1/repeats:10_mean              1015267 ns      1015244 ns           10 bytes/s=984.985M/s ints/s=984.985M/s ns/int=1.01524ns
bench_fmtlib_fmt/dist:2/param:1/repeats:10_median            1014979 ns      1014933 ns           10 bytes/s=985.286M/s ints/s=985.286M/s ns/int=1.01493ns
bench_fmtlib_fmt/dist:2/param:1/repeats:10_stddev                785 ns          778 ns           10 bytes/s=754.047k/s ints/s=754.047k/s ns/int=777.851fs
bench_fmtlib_fmt/dist:2/param:1/repeats:10_cv                   0.08 %          0.08 %            10 bytes/s=0.08% ints/s=0.08% ns/int=0.08%
bench_fmtlib_fmt/dist:2/param:1/repeats:10_max               1016852 ns      1016838 ns           10 bytes/s=985.702M/s ints/s=985.702M/s ns/int=1.01684ns
bench_fmtlib_fmt/dist:2/param:4/repeats:10_mean              2251982 ns      2251934 ns           10 bytes/s=1.77625G/s ints/s=444.063M/s ns/int=2.25193ns
bench_fmtlib_fmt/dist:2/param:4/repeats:10_median            2251927 ns      2251843 ns           10 bytes/s=1.77632G/s ints/s=444.081M/s ns/int=2.25184ns
bench_fmtlib_fmt/dist:2/param:4/repeats:10_stddev               1335 ns         1338 ns           10 bytes/s=1.05471M/s ints/s=263.679k/s ns/int=1.33754ps
bench_fmtlib_fmt/dist:2/param:4/repeats:10_cv                   0.06 %          0.06 %            10 bytes/s=0.06% ints/s=0.06% ns/int=0.06%
bench_fmtlib_fmt/dist:2/param:4/repeats:10_max               2254505 ns      2254432 ns           10 bytes/s=1.77766G/s ints/s=444.416M/s ns/int=2.25443ns
bench_fmtlib_fmt/dist:2/param:8/repeats:10_mean              4536337 ns      4536272 ns           10 bytes/s=1.76357G/s ints/s=220.446M/s ns/int=4.53627ns
bench_fmtlib_fmt/dist:2/param:8/repeats:10_median            4535409 ns      4535305 ns           10 bytes/s=1.76394G/s ints/s=220.492M/s ns/int=4.53531ns
bench_fmtlib_fmt/dist:2/param:8/repeats:10_stddev               7229 ns         7232 ns           10 bytes/s=2.81052M/s ints/s=351.315k/s ns/int=7.23194ps
bench_fmtlib_fmt/dist:2/param:8/repeats:10_cv                   0.16 %          0.16 %            10 bytes/s=0.16% ints/s=0.16% ns/int=0.16%
bench_fmtlib_fmt/dist:2/param:8/repeats:10_max               4549775 ns      4549784 ns           10 bytes/s=1.76853G/s ints/s=221.066M/s ns/int=4.54978ns
bench_fmtlib_fmt/dist:2/param:12/repeats:10_mean             7784536 ns      7784404 ns           10 bytes/s=1.60862G/s ints/s=134.052M/s ns/int=7.7844ns
bench_fmtlib_fmt/dist:2/param:12/repeats:10_median           6880433 ns      6880220 ns           10 bytes/s=1.74413G/s ints/s=145.344M/s ns/int=6.88022ns
bench_fmtlib_fmt/dist:2/param:12/repeats:10_stddev           2046586 ns      2046555 ns           10 bytes/s=286.329M/s ints/s=23.8607M/s ns/int=2.04655ns
bench_fmtlib_fmt/dist:2/param:12/repeats:10_cv                 26.29 %         26.29 %            10 bytes/s=17.80% ints/s=17.80% ns/int=26.29%
bench_fmtlib_fmt/dist:2/param:12/repeats:10_max             13126002 ns     13125786 ns           10 bytes/s=1.75081G/s ints/s=145.901M/s ns/int=13.1258ns
bench_fmtlib_fmt/dist:2/param:16/repeats:10_mean             9482012 ns      9481851 ns           10 bytes/s=1.68752G/s ints/s=105.47M/s ns/int=9.48185ns
bench_fmtlib_fmt/dist:2/param:16/repeats:10_median           9445959 ns      9445675 ns           10 bytes/s=1.6939G/s ints/s=105.869M/s ns/int=9.44567ns
bench_fmtlib_fmt/dist:2/param:16/repeats:10_stddev             70144 ns        70186 ns           10 bytes/s=12.4604M/s ints/s=778.778k/s ns/int=70.1856ps
bench_fmtlib_fmt/dist:2/param:16/repeats:10_cv                  0.74 %          0.74 %            10 bytes/s=0.74% ints/s=0.74% ns/int=0.74%
bench_fmtlib_fmt/dist:2/param:16/repeats:10_max              9579158 ns      9578935 ns           10 bytes/s=1.69948G/s ints/s=106.218M/s ns/int=9.57894ns
bench_fmtlib_fmt/dist:2/param:19/repeats:10_mean            12418773 ns     12418562 ns           10 bytes/s=1.52997G/s ints/s=80.5248M/s ns/int=12.4186ns
bench_fmtlib_fmt/dist:2/param:19/repeats:10_median          12410493 ns     12410434 ns           10 bytes/s=1.53097G/s ints/s=80.5774M/s ns/int=12.4104ns
bench_fmtlib_fmt/dist:2/param:19/repeats:10_stddev             21924 ns        21888 ns           10 bytes/s=2.69103M/s ints/s=141.633k/s ns/int=21.8884ps
bench_fmtlib_fmt/dist:2/param:19/repeats:10_cv                  0.18 %          0.18 %            10 bytes/s=0.18% ints/s=0.18% ns/int=0.18%
bench_fmtlib_fmt/dist:2/param:19/repeats:10_max             12468387 ns     12468013 ns           10 bytes/s=1.53261G/s ints/s=80.6636M/s ns/int=12.468ns
```

</details>
