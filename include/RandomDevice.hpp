#pragma once
#include <random>

class RandomDevice
{
  private:
    std::mt19937 m_engine;

  public:
    explicit RandomDevice();
    RandomDevice(const RandomDevice &) = delete;

    int randomInt(int min, int max);
    int randomNonZeroInt(int min, int max);
    float randomFloat(float min, float max);
};
