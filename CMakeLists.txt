cmake_minimum_required(VERSION 3.14)

project(
    itoa_benchmarks
    VERSION 0.1.0
    DESCRIPTION "Benchmarks for integer-to-string conversion implementations"
    LANGUAGES C CXX
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BENCHMARK_BUILD_SIMDITOA          "Include simditoa::to_chars contender"            ON)
option(BENCHMARK_BUILD_NULL              "Include null/no-op contender"                    ON)
option(BENCHMARK_BUILD_STD_TO_CHARS      "Include std::to_chars contender"                 ON)
option(BENCHMARK_BUILD_YY_ITOA           "Include yy_itoa contender"                       ON)
option(BENCHMARK_BUILD_JEAIII_ITOA       "Include jeaiii/itoa contender"                   ON)
option(BENCHMARK_BUILD_TENCENT_RAPIDJSON "Include Tencent/rapidjson branchlut i64toa"      ON)
option(BENCHMARK_BUILD_FMTLIB_FMT        "Include fmtlib/fmt format_int contender"         ON)

add_subdirectory(benchmarks)
