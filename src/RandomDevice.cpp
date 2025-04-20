#include "RandomDevice.hpp"

RandomDevice::RandomDevice()
{
    std::random_device device;
    m_engine = std::mt19937(device());
}

int RandomDevice::randomInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_engine);
}

int RandomDevice::randomNonZeroInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    int value = dist(m_engine);

    while (true)
    {
        if (value != 0)
        {
            return value;
        }

        value = dist(m_engine);
    }
}

float RandomDevice::randomFloat(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_engine);
}
