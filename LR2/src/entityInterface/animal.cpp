#include "animal.hpp"
#include <random>

std::pair<const int, const int> animal::move()
{
    return {(random()%3 - 1)*speed,
               (random()%3 - 1)*speed};
}

