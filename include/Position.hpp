#pragma once
#include "Dimensions.hpp"
#include "RandomDevice.hpp"
#include "SFML/System/Vector2.hpp"

class Position
{
  private:
    Dimensions m_screenDimensions;
    RandomDevice m_randomDevice;

  public:
    explicit Position(const Dimensions &screenDimensions, RandomDevice &randomDevice);
    Position(const Position &) = delete;
    sf::Vector2f random();
};
