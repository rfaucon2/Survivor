#ifndef UTILITARY
#define UTILITARY

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <time.h>
#include <random>
#include <map>
#include <unordered_map>

namespace util
{
    float size(sf::Vector2f v);
    sf::Vector2f normalize(sf::Vector2f v);
    void print_vec(sf::Vector2f v, bool ln = true);
} // namespace util



#endif