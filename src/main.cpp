#include "Config.hpp"
#include "Dimensions.hpp"
#include "Line.hpp"
#include "Position.hpp"
#include "RandomDevice.hpp"

int main()
{
    auto mode = sf::VideoMode({Config::WIN_WIDTH, Config::WIN_HEIGHT});
    sf::RenderWindow window(mode, Config::WIN_TITLE);
    window.setFramerateLimit(60);

    Dimensions screenDimensions{Config::WIN_WIDTH, Config::WIN_HEIGHT};
    RandomDevice randomDevice{};
    Position positions{screenDimensions, randomDevice};

    uint particleCount{Config::PARTICLE_COUNT};
    std::vector<Particle> particles;
    particles.reserve(particleCount);

    for (uint i = 0; i < particleCount; i++)
    {
        particles.push_back(Particle{positions.random(), Config::PARTICLE_SPEED, randomDevice});
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        drawProximityLines(window, particles, Config::DISTANCE_THRESHOLD);
        for (auto &particle : particles)
        {
            window.draw(particle);
            particle.update();
        }

        window.display();
    }
}
