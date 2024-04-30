#ifndef PLAYER
#define PLAYER

#include "Utilitary.h"

class Player
{
public:
    const float WIDTH = 50;
    const float HEIGHT = 100;

private:
    sf::Rect<float> m_rect;
    float           m_speed;

public:
    Player();
    
    void Update(float dt);
    void Draw(sf::RenderTarget* target);

    // Accessors
    sf::Vector2f get_pos() const;
    sf::Vector2f get_size() const;
};



#endif