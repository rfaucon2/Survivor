#include "Ennemy.h"

Ennemy::Ennemy(sf::Vector2f pos)
    : m_pos(pos), m_size(WIDTH, HEIGHT), m_rect(m_pos, m_size)
{
    
}

void Ennemy::update(float dt, sf::Vector2f player_pos)
{
    this->m_pos += dt * SPEED * util::normalize(player_pos - this->m_pos);
}

void Ennemy::draw(sf::RenderWindow* window)
{
    sf::CircleShape sprite(WIDTH);
    sprite.setPosition(this->m_pos);
    sprite.setFillColor(sf::Color(65, 120, 30));
    window->draw(sprite);

    
}