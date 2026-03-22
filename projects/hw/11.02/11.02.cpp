#include <benchmark/benchmark.h>
#include <functional>
#include <cstdint>
#include <iostream>


[[gnu::noinline]] static void increase(std::uint64_t & acc)
{
    acc += 1;
}


[[gnu::noinline]] static void free_function(std::uint64_t & acc)
{
    increase(acc);
}


class WorkingClass
{
public:
    [[gnu::noinline]] void member_function(std::uint64_t & acc)
    {
        increase(acc);
    }
};


class Base
{
public:
    [[gnu::noinline]] virtual void virtual_function(std::uint64_t & acc) = 0;
    virtual ~Base() = default;
};


class Derived : public Base
{
public:
    [[gnu::noinline]] void virtual_function(std::uint64_t & acc) override
    {
        increase(acc);
    }
};


class Functor
{
public:
    [[gnu::noinline]] void operator()(std::uint64_t & acc)
    {
        increase(acc);
    }
};



static void BM_free_function(benchmark::State & state)
{
    std::uint64_t acc = 0;
    for (auto iter : state)
    {
        free_function(acc);
        benchmark::DoNotOptimize(acc);
    }
}

static void BM_member_function(benchmark::State & state)
{
    WorkingClass obj;
    std::uint64_t acc = 0;
    for (auto iter : state)
    {
        obj.member_function(acc);
        benchmark::DoNotOptimize(acc);
    }
}

static void BM_virtual_function(benchmark::State & state)
{
    Derived derived;
    Base* base_ptr = &derived;
    std::uint64_t acc = 0;
    for (auto iter : state)
    {
        base_ptr->virtual_function(acc);
        benchmark::DoNotOptimize(acc);
    }
}

static void BM_functor(benchmark::State & state)
{
    Functor functor;
    std::uint64_t acc = 0;
    for (auto iter : state)
    {
        functor(acc);
        benchmark::DoNotOptimize(acc);
    }
}

static void BM_lambda_auto(benchmark::State & state)
{
    auto lambda = [](std::uint64_t & acc) { increase(acc); };
    std::uint64_t acc = 0;
    for (auto iter : state)
    {
        lambda(acc);
        benchmark::DoNotOptimize(acc);
    }
}

static void BM_lambda_std_function(benchmark::State & state)
{
    std::function<void(std::uint64_t &)> f = [](std::uint64_t & acc) { increase(acc); };
    std::uint64_t acc = 0;
    for (auto iter : state)
    {
        f(acc);
        benchmark::DoNotOptimize(acc);
    }
}


BENCHMARK(BM_free_function);
BENCHMARK(BM_member_function);
BENCHMARK(BM_virtual_function);
BENCHMARK(BM_functor);
BENCHMARK(BM_lambda_auto);
BENCHMARK(BM_lambda_std_function);
///////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv)
{
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}
