#pragma once
#include "Particle.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

void renderLine(sf::RenderWindow &window, const sf::Vector2f &start, const sf::Vector2f &end,
                sf::Color color = sf::Color(47, 98, 13));

void drawProximityLines(sf::RenderWindow &window, const std::vector<Particle> &particles, float distanceThreshold);
