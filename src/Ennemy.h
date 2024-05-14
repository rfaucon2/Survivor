#ifndef ENNEMY
#define ENNEMY

#include "Utilitary.h"
#include <SFML/Graphics.hpp>

typedef enum
{
    GOBLIN = 0,
    SPIRIT,
    SIZE
} e_monsters;


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

    static std::map<e_monsters, sf::Texture> textures;
public:
    Ennemy(sf::Vector2f pos, float speed, float radius, e_monsters type = e_monsters::SPIRIT);
    ~Ennemy();

    void update(float dt, sf::Vector2f player_pos);

    void draw(sf::RenderWindow* window);

    void deal_damange(float dmg);
    float get_health() const;
    sf::Vector2f get_pos() const;
};

#endif