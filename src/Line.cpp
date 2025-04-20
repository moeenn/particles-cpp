#include "Line.hpp"

void renderLine(sf::RenderWindow &window, const sf::Vector2f &start, const sf::Vector2f &end, sf::Color color)
{

    sf::Vertex line[] = {{start, color}, {end, color}};
    window.draw(line, 2, sf::PrimitiveType::Lines);
}

void drawProximityLines(sf::RenderWindow &window, const std::vector<Particle> &particles, float distanceThreshold)
{

    if (particles.size() < 2)
        return;

    int max = particles.size();
    int i = 0;
    int j = 1;

    while (i < j)
    {
        Particle a = particles[i];
        Particle b = particles[j];

        if (a.distance(b) <= distanceThreshold)
        {
            renderLine(window, a.getPosition(), b.getPosition());
        }

        j++;
        if (j == max)
        {
            i++;
            j = i + 1;
        }

        if (i == max - 1)
            break;
    }
}
