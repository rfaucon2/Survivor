#include "Utilitary.h"

float util::size(sf::Vector2f v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

sf::Vector2f util::normalize(sf::Vector2f v)
{
    return v / util::size(v);
}