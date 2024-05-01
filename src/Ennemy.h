#ifndef ENNEMY
#define ENNEMY

#include "Utilitary.h"
#include <SFML/Graphics.hpp>

class Ennemy
{
public:
    const uint32_t WIDTH  = 15U;
    const uint32_t HEIGHT = 15U;
    const float    SPEED  = 700.0F;
private:
    sf::Vector2f    m_pos;
    sf::Vector2f    m_size;
    sf::Rect<float> m_rect;

public:
    Ennemy(sf::Vector2f pos);
    ~Ennemy();

    void update(float dt, sf::Vector2f player_pos);

    void draw(sf::RenderWindow* window);
};

#endif