#pragma once
#include "Config.hpp"
#include "RandomDevice.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Particle : public sf::CircleShape
{
  public:
    int m_xSpeed;
    int m_ySpeed;

    explicit Particle(sf::Vector2f position, int speed, RandomDevice &randomDevice, float radius = 2.0f,
                      sf::Color color = sf::Color::Green);

    void update();
    float distance(const Particle &other);
};
