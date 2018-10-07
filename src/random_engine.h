#ifndef RANDOM_ENGINE_H
#define RANDOM_ENGINE_H

#include <random>
#include <cstdint>

static std::random_device rd;
static std::mt19937 mt(rd());
static std::uniform_real_distribution<double> dist(0.0, 1.0);

// Not already used!
class random_engine
{
public:
  // seed
  void seed(int32_t new_seed)
  {
    engine.seed(new_seed);
  }

  // uniform distribution
  double uniform_double()
  {
    return std::uniform_real_distribution<double>()(engine);
  }

  double uniform_double_range(double min, double max)
  {
    return std::uniform_real_distribution<double>(min, max)(engine);
  }

  int32_t uniform_int()
  {
    return std::uniform_int_distribution<int32_t>()(engine);
  }

  int32_t uniform_int_range(int32_t min, int32_t max)
  {
    return std::uniform_int_distribution<int32_t>(min, max)(engine);
  }

  bool uniform_bool()
  {
    return (uniform_int_range(0, 1) == 1);
  }

private:
  static std::minstd_rand engine;
};

#endif // !RANDOM_ENGINE_H