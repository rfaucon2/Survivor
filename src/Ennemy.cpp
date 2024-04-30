#include "Ennemy.h"

Ennemy::Ennemy()
    : m_pos(0, 0), m_size(WIDTH, HEIGHT), m_rect(m_pos, m_size)
{
    
}

void Ennemy::update(float dt, sf::Vector2f player_pos)
{
    this->m_pos += SPEED * util::normalize(player_pos - this->m_pos);
}

void Ennemy::draw(sf::RenderWindow* window)
{
    sf::CircleShape sprite(WIDTH);
    sprite.setPosition(this->m_pos);
    sprite.setFillColor(sf::Color(65, 120, 30));
    window->draw(sprite);
}