#ifndef ENNEMY
#define ENNEMY

#include "Utilitary.h"
#include <SFML/Graphics.hpp>

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
    float           m_health;

public:
    Ennemy(sf::Vector2f pos, float speed, float radius);
    ~Ennemy();

    void update(float dt, sf::Vector2f player_pos);

    void draw(sf::RenderWindow* window);

    void deal_damange(float dmg);
    float get_health() const;
    sf::Vector2f get_pos() const;
};

#endif