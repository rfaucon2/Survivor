#ifndef UTILITARY
#define UTILITARY

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>
#include <random>

namespace util
{
    float size(sf::Vector2f v);
    sf::Vector2f normalize(sf::Vector2f v);
    void print_vec(sf::Vector2f v, bool ln = true);
} // namespace util



#endif