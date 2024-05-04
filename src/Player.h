#ifndef PLAYER
#define PLAYER

#include "Utilitary.h"


class Player
{
public:
    const float WIDTH = 50;
    const float HEIGHT = 100;
    const int   BASE_MAXHP = 100;

private:
    sf::Rect<float> m_rect;
    float           m_speed;
    int             m_maxhp;
    int             m_hp;

public:
    Player();
    
    void Update(float dt);
    void Draw(sf::RenderTarget* target);

    // Accessors
    sf::Vector2f get_pos() const;
    sf::Vector2f get_size() const;
    int get_hp() const;
    int get_maxhp() const;
};



#endif