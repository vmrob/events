#include <events/Publisher.h>

#include <benchmark/benchmark.h>

struct Topic1 {
    using Callback = void();
};

static void BM_SingleSubscriber(benchmark::State& state) {
    events::Publisher p;

    auto subscriber = p.subscribe<Topic1>();

    subscriber->registerCallback([] {});

    while (state.KeepRunning()) {
        p.publish<Topic1>();
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations());
}

BENCHMARK(BM_SingleSubscriber);

static void BM_MultiSubscriber(benchmark::State& state) {
    events::Publisher p;

    auto s1 = p.subscribe<Topic1>();
    auto s2 = p.subscribe<Topic1>();

    for (size_t i = 0; i < state.range(0); ++i) {
        auto s = p.subscribe<Topic1>();
        s->registerCallback([] {});
    }

    while (state.KeepRunning()) {
        p.publish<Topic1>();
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
}

BENCHMARK(BM_MultiSubscriber)->Range(2, 2 << 6);

static void BM_MultiCallback(benchmark::State& state) {
    events::Publisher p;

    auto s1 = p.subscribe<Topic1>();
    auto s2 = p.subscribe<Topic1>();

    auto s = p.subscribe<Topic1>();
    for (size_t i = 0; i < state.range(0); ++i) {
        s->registerCallback([] {});
    }

    while (state.KeepRunning()) {
        p.publish<Topic1>();
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
}

BENCHMARK(BM_MultiCallback)->Range(2, 2 << 6);

namespace {
int noop() {
    volatile int i = 0;
    return i;
}
}  // namespace

static void BM_Control(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(noop());
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_Control);

BENCHMARK_MAIN();
