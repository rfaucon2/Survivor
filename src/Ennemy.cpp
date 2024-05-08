#include "Ennemy.h"

const float Ennemy::BASE_SPEED = 125;
const float Ennemy::BASE_RADIUS = 13;

Ennemy::Ennemy(sf::Vector2f pos, float speed, float radius)
    : m_pos(pos), m_radius(radius), m_speed(speed), m_rect(m_pos, sf::Vector2f(radius, radius))
{
}
Ennemy::~Ennemy()
{

}

void Ennemy::update(float dt, sf::Vector2f player_pos)
{
    this->m_pos += dt * this->m_speed * util::normalize(player_pos - this->m_pos);
}

void Ennemy::draw(sf::RenderWindow* window)
{
    sf::CircleShape sprite(this->m_radius);
    sprite.setPosition(this->m_pos);
    sprite.setOrigin(sf::Vector2f(this->m_radius, this->m_radius) * 0.5f);
    sprite.setFillColor(sf::Color(65, 120, 30));
    window->draw(sprite);
}

sf::Vector2f Ennemy::get_pos() const
{
    return this->m_pos;
}