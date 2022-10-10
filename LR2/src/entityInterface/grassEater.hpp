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
               const uint _size, sex_t sex,
               const uint speed = 1,
               uint _chanceToSurvive = 0, const char* spritePath = nullptr)
        : animal(name, health, _size, sex, speed, spritePath)
    {
        if (_chanceToSurvive > 1 or _chanceToSurvive < 0)
            _chanceToSurvive = 0;
        this->chanceToSurvive = _chanceToSurvive;
    }
    ~grassEater() override
    {
    }

    std::string getName() { return name; }
    double getChanceToSurvive() { return chanceToSurvive; }
    virtual bool isAlive() { return fabs(random() % 10) <= (chanceToSurvive * 10 - 1); }
    virtual bool isLovely(grassEater* partner) { return this->sex != partner->sex; }
};