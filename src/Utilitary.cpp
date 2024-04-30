#include "Utilitary.h"

float util::size(sf::Vector2f v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

sf::Vector2f util::normalize(sf::Vector2f v)
{
    if(util::size(v) == 0)
        return sf::Vector2f(0, 0);
    return v / util::size(v);
}