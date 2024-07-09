#ifndef ENNEMY
#define ENNEMY

#include "Utilitary.h"
#include <SFML/Graphics.hpp>

typedef enum
{
    GOBLIN = 0,
    SPIRIT,
    SKELETON,
    DRAGON,
    SIZE
} e_monsters;

const std::map<e_monsters, std::vector<float>> ENNEMY_STATS = {
//  {type, {health, damage, exp}}
    {e_monsters::GOBLIN, {6.0f,  9.0f, 10.f}},
    {e_monsters::SPIRIT, {11.0f, 7.0f, 21.f}},
    {e_monsters::SKELETON, {21.0f, 13.0f, 30.f}},
    {e_monsters::DRAGON, {60.0f, 50.0f, 100.f}}
};

class Ennemy
{
public:
    static const float BASE_SPEED;
    static const float BASE_RADIUS;

    sf::Vector2f    m_pos;
private:
    float           m_speed;
    float           m_radius;
    sf::Rect<float> m_rect;
    sf::Sprite      m_sprite;
    float           m_health;
    float           m_dmg;
    float           m_exp;

    static std::map<e_monsters, sf::Texture> textures;
public:
    Ennemy(sf::Vector2f pos, float speed = Ennemy::BASE_SPEED, float radius = Ennemy::BASE_RADIUS, e_monsters type = e_monsters::SPIRIT);
    ~Ennemy();

    void update(float dt, sf::Vector2f player_pos);

    void draw(sf::RenderWindow* window);

    bool deal_damage(float dmg);
    float get_health() const;
    sf::Vector2f get_pos() const;
    float get_dmg() const;
    float get_exp() const;
};

#endif