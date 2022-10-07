#pragma once

#include <string>
#include "animal.hpp"
#include <random>

class grassEater : public animal
{
protected:
    double chanceToSurvive;

public:
    grassEater(const std::string name, const int health,
               const unsigned int _size, sex_t sex,
               const unsigned int stepsLeft, const unsigned int speed = 1,
               unsigned int _chanceToSurvive = 0)
        : animal(name, health, _size, sex, stepsLeft, speed)
    {
        if (_chanceToSurvive > 1 or _chanceToSurvive < 0)
            _chanceToSurvive = 0;
        this->chanceToSurvive = _chanceToSurvive;
    }
    ~grassEater()
    {
    }

    std::string getName() { return name; }
    virtual bool isAlive() { return fabs(random() % 10) <= (chanceToSurvive * 10 - 1); }
    virtual bool isLovely(grassEater* partner) { return this->sex != partner->sex; }
};