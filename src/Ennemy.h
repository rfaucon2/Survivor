#ifndef ENNEMY
#define ENNEMY

#include "Utilitary.h"
#include <SFML/Graphics.hpp>

typedef enum
{
    GOBLIN,
    SPIRIT
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

    static std::map<e_monsters, sf::Texture> textures;
public:
    Ennemy(sf::Vector2f pos, float speed, float radius, e_monsters type = e_monsters::SPIRIT);
    ~Ennemy();

    void update(float dt, sf::Vector2f player_pos);

    void draw(sf::RenderWindow* window);
};

#endif