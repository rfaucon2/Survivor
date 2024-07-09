#include "Ennemy.h"

std::map<e_monsters, sf::Texture> Ennemy::textures;

const float Ennemy::BASE_SPEED = 125;
const float Ennemy::BASE_RADIUS = 90;

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
        placeholder.loadFromFile("resources/ennemies/skeleton.png");
        Ennemy::textures[e_monsters::SKELETON] = sf::Texture(placeholder);
        placeholder.loadFromFile("resources/ennemies/dragon.png");
        Ennemy::textures[e_monsters::DRAGON] = sf::Texture(placeholder);
    }
    this->m_health = ENNEMY_STATS.at(type)[0];
    this->m_dmg = ENNEMY_STATS.at(type)[1];
    this->m_exp = ENNEMY_STATS.at(type)[2];

    this->m_radius *= sqrt(m_health / 7);

    this->m_sprite.setTexture(Ennemy::textures[type]);
    this->m_sprite.setOrigin(this->m_sprite.getGlobalBounds().getSize() * 0.5f);
    this->m_sprite.setScale(sf::Vector2f(this->m_radius / Ennemy::textures[type].getSize().x, this->m_radius / Ennemy::textures[type].getSize().y));
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

bool Ennemy::deal_damage(float dmg)
{
    this->m_health -= dmg;
    return this->m_health <= 0;
}
float Ennemy::get_health() const
{
    return this->m_health;
}
sf::Vector2f Ennemy::get_pos() const
{
    return this->m_pos;
}

float Ennemy::get_dmg() const
{
    return this->m_dmg;
}
float Ennemy::get_exp() const
{
    return this->m_exp;
}

