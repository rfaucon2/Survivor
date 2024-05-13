#include "Ennemy.h"

std::map<e_monsters, sf::Texture> Ennemy::textures;

const float Ennemy::BASE_SPEED = 125;
const float Ennemy::BASE_RADIUS = 13;

Ennemy::Ennemy(sf::Vector2f pos, float speed, float radius, e_monsters type)
    : m_pos(pos), m_radius(radius), m_speed(speed), m_rect(m_pos, sf::Vector2f(radius, radius))
{
    if (Ennemy::textures.empty())
    {
        sf::Texture placeholder;

        placeholder.loadFromFile("resources/ennemies/goblin.png");
        Ennemy::textures[e_monsters::GOBLIN] = sf::Texture(placeholder);
        placeholder.loadFromFile("resources/ennemies/spirit.png");
        Ennemy::textures[e_monsters::SPIRIT] = sf::Texture(placeholder);
    }
    this->m_sprite.setTexture(Ennemy::textures[type]);
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
    this->m_sprite.setPosition(this->m_pos);
    window->draw(this->m_sprite);
}

void Ennemy::deal_damange(float dmg)
{
    this->m_health -= dmg;
}
float Ennemy::get_health() const
{
    return this->m_health;
}
sf::Vector2f Ennemy::get_pos() const
{
    return this->m_pos;
}