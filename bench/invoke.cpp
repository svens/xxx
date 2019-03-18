#include <benchmark/benchmark.h>
#include <ctime>
#include <functional>


namespace {


auto r = static_cast<size_t>(time(nullptr));


void invoke_lambda (benchmark::State &state)
{
  auto f = [&]()
  {
    return r * state.iterations();
  };

  for (auto _: state)
  {
    benchmark::DoNotOptimize(f());
  }
}
BENCHMARK(invoke_lambda);


void invoke_method (benchmark::State &state)
{
  struct op
  {
    benchmark::State &state_;

    op (benchmark::State &state)
      : state_(state)
    { }

    size_t run () const noexcept
    {
      return r * state_.iterations();
    }
  } f{state};

  for (auto _: state)
  {
    benchmark::DoNotOptimize(f.run());
  }
}
BENCHMARK(invoke_method);


void invoke_static_method (benchmark::State &state)
{
  struct op
  {
    static size_t run (benchmark::State &state) noexcept
    {
      return r * state.iterations();
    }
  } f;

  for (auto _: state)
  {
    benchmark::DoNotOptimize(f.run(state));
  }
}
BENCHMARK(invoke_static_method);


struct base_op
{
  virtual ~base_op () noexcept = default;
  virtual size_t run () const noexcept = 0;
};


void invoke_virtual_method (benchmark::State &state)
{
  struct op
    : public base_op
  {
    benchmark::State &state_;

    op (benchmark::State &state)
      : state_(state)
    { }

    size_t run () const noexcept final override
    {
      return r * state_.iterations();
    }
  } impl{state};

  base_op &f = impl;
  for (auto _: state)
  {
    benchmark::DoNotOptimize(f.run());
  }
}
BENCHMARK(invoke_virtual_method);


template <typename F>
struct op
  : public base_op
{
  F fn_;
  benchmark::State &state_;

  op (F fn, benchmark::State &state) noexcept
    : fn_(fn)
    , state_(state)
  { }

  size_t run () const noexcept final override
  {
    return fn_(state_);
  }
};


void invoke_virtual_method_with_lambda (benchmark::State &state)
{
    auto lambda = [](benchmark::State &state) noexcept
    {
        return r * state.iterations();
    };
    op<decltype(lambda)> impl{lambda, state};
    base_op &f = impl;

    for (auto _: state)
    {
        benchmark::DoNotOptimize(f.run());
    }
}
BENCHMARK(invoke_virtual_method_with_lambda);


size_t f (benchmark::State &state) noexcept
{
    return r * state.iterations();
}


void invoke_function_ptr (benchmark::State &state)
{
    auto fp = &f;
    for (auto _: state)
    {
        benchmark::DoNotOptimize((*fp)(state));
    }
}
BENCHMARK(invoke_function_ptr);


void invoke_std_function (benchmark::State &state)
{
    std::function<size_t(benchmark::State &)> f = [](benchmark::State &s)
    {
        return r * s.iterations();
    };

    for (auto _: state)
    {
        benchmark::DoNotOptimize(f(state));
    }
}
BENCHMARK(invoke_std_function);


} // namespace
