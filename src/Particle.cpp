#include "Particle.hpp"

Particle::Particle(sf::Vector2f position, int speed, RandomDevice &randomDevice, float radius, sf::Color color)
{
    setRadius(radius);
    setFillColor(color);
    setPosition(position);

    m_xSpeed = randomDevice.randomNonZeroInt(-1 * speed, speed);
    m_ySpeed = randomDevice.randomNonZeroInt(-1 * speed, speed);
}

void Particle::update()
{
    sf::Vector2f position = getPosition();
    position.x += m_xSpeed;
    position.y += m_ySpeed;

    if (position.x < 0 || position.x > Config::WIN_WIDTH)
    {
        m_xSpeed *= -1;
    }

    if (position.y < 0 || position.y > Config::WIN_HEIGHT)
    {
        m_ySpeed *= -1;
    }

    setPosition(position);
}

float Particle::distance(const Particle &other)
{
    sf::Vector2f pos = getPosition();
    float xSquared = std::pow((pos.x - other.getPosition().x), 2);
    float ySquared = std::pow((pos.y - other.getPosition().y), 2);
    return std::sqrt(xSquared + ySquared);
}
