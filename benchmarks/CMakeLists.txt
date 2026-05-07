include(FetchContent)

# ---- google/benchmark (always) ----
FetchContent_Declare(
    google_benchmark
    URL https://github.com/google/benchmark/archive/refs/tags/v1.9.5.zip
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_WERROR OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(google_benchmark)

# ---- itoa_benchmarks executable (sources appended per-contender below) ----
add_executable(itoa_benchmarks)
target_link_libraries(itoa_benchmarks PRIVATE benchmark::benchmark_main)
target_include_directories(itoa_benchmarks PRIVATE ${CMAKE_SOURCE_DIR}/common)

if(NOT MSVC)
  target_compile_options(itoa_benchmarks PRIVATE -Wall -Wextra)
endif()

# ---- simditoa ----
if(BENCHMARK_BUILD_SIMDITOA)
  FetchContent_Declare(
      simditoa
      GIT_REPOSITORY https://github.com/simditoa/simditoa.git
      GIT_TAG main
  )
  FetchContent_MakeAvailable(simditoa)
  target_sources(itoa_benchmarks PRIVATE simditoa.cpp)
  target_link_libraries(itoa_benchmarks PRIVATE simditoa::simditoa)
endif()

# ---- null (no extra deps) ----
if(BENCHMARK_BUILD_NULL)
  target_sources(itoa_benchmarks PRIVATE null.cpp)
endif()

# ---- std::to_chars (no extra deps) ----
if(BENCHMARK_BUILD_STD_TO_CHARS)
  target_sources(itoa_benchmarks PRIVATE std_to_chars.cpp)
endif()

# ---- yy_itoa (from c_numconv_benchmark) ----
if(BENCHMARK_BUILD_YY_ITOA)
  FetchContent_Declare(
      c_numconv_benchmark
      GIT_REPOSITORY https://github.com/ibireme/c_numconv_benchmark.git
      GIT_TAG master
      SOURCE_SUBDIR _skip_numconv_cmake
  )
  FetchContent_MakeAvailable(c_numconv_benchmark)
  add_library(yy_itoa STATIC ${c_numconv_benchmark_SOURCE_DIR}/src/itoa/itoa_yy.c)
  set_target_properties(yy_itoa PROPERTIES C_STANDARD 99 POSITION_INDEPENDENT_CODE ON)
  target_sources(itoa_benchmarks PRIVATE yy_itoa.cpp)
  target_link_libraries(itoa_benchmarks PRIVATE yy_itoa)
endif()

# ---- jeaiii::to_text_from_integer ----
if(BENCHMARK_BUILD_JEAIII_ITOA)
  FetchContent_Declare(
      jeaiii_itoa
      GIT_REPOSITORY https://github.com/jeaiii/itoa.git
      GIT_TAG main
  )
  FetchContent_MakeAvailable(jeaiii_itoa)
  add_library(jeaiii_itoa_iface INTERFACE)
  target_include_directories(jeaiii_itoa_iface INTERFACE ${jeaiii_itoa_SOURCE_DIR}/include/itoa)
  target_sources(itoa_benchmarks PRIVATE jeaiii_itoa.cpp)
  target_link_libraries(itoa_benchmarks PRIVATE jeaiii_itoa_iface)
endif()

# ---- rapidjson (header-only; skip its CMake) ----
if(BENCHMARK_BUILD_TENCENT_RAPIDJSON)
  FetchContent_Declare(
      rapidjson
      GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
      GIT_TAG v1.1.0
      SOURCE_SUBDIR _skip_rapidjson_cmake
  )
  FetchContent_MakeAvailable(rapidjson)
  add_library(rapidjson_iface INTERFACE)
  target_include_directories(rapidjson_iface INTERFACE ${rapidjson_SOURCE_DIR}/include)
  target_sources(itoa_benchmarks PRIVATE tencent_rapidjson.cpp)
  target_link_libraries(itoa_benchmarks PRIVATE rapidjson_iface)
endif()

# ---- fmt::format_int ----
if(BENCHMARK_BUILD_FMTLIB_FMT)
  FetchContent_Declare(
      fmt
      GIT_REPOSITORY https://github.com/fmtlib/fmt.git
      GIT_TAG 11.1.4
  )
  set(FMT_INSTALL OFF CACHE BOOL "" FORCE)
  set(FMT_TEST OFF CACHE BOOL "" FORCE)
  set(FMT_DOC OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(fmt)
  target_sources(itoa_benchmarks PRIVATE fmtlib_fmt.cpp)
  target_link_libraries(itoa_benchmarks PRIVATE fmt::fmt)
endif()
