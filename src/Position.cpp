#include "Position.hpp"

Position::Position(const Dimensions &screenDimensions, RandomDevice &randomDevice)
{
    m_screenDimensions = screenDimensions;
    m_randomDevice = randomDevice;
}

sf::Vector2f Position::random()
{
    float x = m_randomDevice.randomFloat(0, m_screenDimensions.m_width);
    float y = m_randomDevice.randomFloat(0, m_screenDimensions.m_height);
    return sf::Vector2f(x, y);
}
