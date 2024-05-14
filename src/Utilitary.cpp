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

void util::print_vec(sf::Vector2f v, bool ln)
{
    std::cout << "<" << v.x << ", " << v.y << ">" << (ln ? '\n' : '\0');
}

sf::Vector2f util::abs(sf::Vector2f v)
{
    return sf::Vector2f(std::abs(v.x), std::abs(v.y));
}

sf::Vector2f util::max(sf::Vector2f v, float x)
{
    return sf::Vector2f(std::max(v.x, x), std::max(v.y, x));
}

sf::Vector2f util::min(sf::Vector2f v, float x)
{
    return sf::Vector2f(std::min(v.x, x), std::min(v.y, x));
}

float util::square_sdf(sf::Vector2f center, sf::Vector2f size, sf::Vector2f point)
{
    sf::Vector2f q = abs(point-center)-size;
    return util::size(max(q, 0.)) + std::min(std::max(q.x, q.y), 0.f);
}
