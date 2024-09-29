#include <benchmark/benchmark.h>
#include "headers/add.h"

static void BM_Add(benchmark::State& state) {
    int a = state.range(0);
    int b = state.range(1);
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum(a, b));
    }
}

BENCHMARK(BM_Add)->Args({1, 1})->Args({10, 10})->Args({100, 100});

BENCHMARK_MAIN();