#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>

namespace config {
constexpr const int WIN_HEIGHT = 600.0;
constexpr const int WIN_WIDTH = 800.0;
const std::string WIN_TITLE = std::string{"Game"};
const int PARTICLE_SPEED = 1;
const int PARTICLE_COUNT = 1500;
const int DISTANCE_THRESHOLD = 50;
}; // namespace config

class Dimentions {
public:
  uint m_width;
  uint m_height;

  explicit Dimentions() = default;
  Dimentions(const Dimentions&) = delete;
  Dimentions(uint width, uint height) : m_width(width), m_height(height) {}
};

class RandomDevice {
private:
  std::mt19937 m_engine;

public:
  explicit RandomDevice() {
    std::random_device device;
    m_engine = std::mt19937(device());
  }

  RandomDevice(const RandomDevice&) = delete; 

  int randomInt(int min, int max) { 
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_engine); 
  }

  int randomNonZeroInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    int value = dist(m_engine);     

    while (true) {
      if (value != 0) {
        return value;
      }

      value = dist(m_engine);
    } 
  }

  float randomFloat(float min, float max) { 
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_engine); 
  }  
};

class Position {
private:
  Dimentions m_screenDimentions;
  RandomDevice m_randomDevice;

public:
  explicit Position(const Dimentions &screenDimentions, RandomDevice &randomDevice)
  {
    m_screenDimentions = screenDimentions;
    m_randomDevice = randomDevice;
  }

  Position(const Position&) = delete;

  sf::Vector2f random() {
    float x = m_randomDevice.randomFloat(0, m_screenDimentions.m_width);
    float y = m_randomDevice.randomFloat(0, m_screenDimentions.m_height);
    return sf::Vector2f(x, y);
  }
};

class Particle : public sf::CircleShape {
public:
  int m_xSpeed;
  int m_ySpeed;

  explicit Particle(sf::Vector2f position, int speed, RandomDevice &randomDevice, float radius = 2.0f,
           sf::Color color = sf::Color::Green) {
    setRadius(radius);
    setFillColor(color);
    setPosition(position);

    m_xSpeed = randomDevice.randomNonZeroInt(-1*speed , speed);
    m_ySpeed = randomDevice.randomNonZeroInt(-1*speed, speed);
   }

  void update() {
    sf::Vector2f position = getPosition();
    position.x += m_xSpeed;
    position.y += m_ySpeed;

    if (position.x < 0 || position.x > config::WIN_WIDTH) {
      m_xSpeed *= -1;
    }

    if (position.y < 0 || position.y > config::WIN_HEIGHT) {
      m_ySpeed *= -1;
    }

    setPosition(position);
  }

  float distance(const Particle& other) {
    sf::Vector2f pos = getPosition();
    float xSquared = std::pow((pos.x - other.getPosition().x), 2);
    float ySquared = std::pow((pos.y - other.getPosition().y), 2);
    return std::sqrt(xSquared + ySquared);
  }
};

void renderLine(sf::RenderWindow& window, const sf::Vector2f &start, const sf::Vector2f &end, sf::Color color = sf::Color(47, 98, 13)) 
{
  sf::Vertex line[] = {{start, color}, {end, color}}; 
  window.draw(line, 2, sf::PrimitiveType::Lines);
}

void drawProximityLines(sf::RenderWindow& window, const std::vector<Particle>& particles, float distanceThreshold) {
  if (particles.size() < 2) return;

  int max = particles.size();
  int i = 0;
  int j = 1;

  while (i < j) {
    Particle a = particles[i];
    Particle b = particles[j];

    if (a.distance(b) <= distanceThreshold) 
    {
      renderLine(window, a.getPosition(), b.getPosition());
    }

    j++;
    if (j == max) {
      i++;
      j = i + 1;
    }

    if (i == max-1) break;
  }
} 

int main() {
  auto mode = sf::VideoMode({config::WIN_WIDTH, config::WIN_HEIGHT});
  sf::RenderWindow window(mode, config::WIN_TITLE);
  window.setFramerateLimit(60);

  Dimentions screenDimentions{config::WIN_WIDTH, config::WIN_HEIGHT};
  RandomDevice randomDevice{};
  Position positions{screenDimentions, randomDevice};

  uint particleCount{config::PARTICLE_COUNT};
  std::vector<Particle> particles;
  particles.reserve(particleCount);

  for (uint i = 0; i < particleCount; i++) {
    particles.push_back(Particle{positions.random(), config::PARTICLE_SPEED, randomDevice});
  }

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear();

    drawProximityLines(window, particles, config::DISTANCE_THRESHOLD);
    for (auto &particle : particles) {
      window.draw(particle);
      particle.update();
    }

    window.display();
  }
}
