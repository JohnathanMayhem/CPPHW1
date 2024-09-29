cmake_minimum_required(VERSION 3.14)
project(sample_cpp_project)

include_directories(headers source)

add_executable(main main.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)


enable_testing()
add_executable(tests test.cpp)
target_link_libraries(tests gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)


include(FetchContent)
FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.7.1
)
FetchContent_MakeAvailable(benchmark)

add_executable(my_benchmark banchmark.cpp source/add.cpp)

target_link_libraries(my_benchmark benchmark::benchmark)