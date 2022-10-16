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
               const int _size,
               sex_t sex, const int speed,
               const double _chanceToSurvive,
               const int starveTime,
               const std::string spritePath)
        : chanceToSurvive(_chanceToSurvive), animal(name, health, _size, sex, speed, starveTime, spritePath)
    {
        if (_chanceToSurvive > 1 or _chanceToSurvive < 0 or speed < 0)
            throw "eror when construct object, type: grassEater";
    }
    ~grassEater() override
    {
    }

    friend std::ostream &operator<<(std::ostream &to, grassEater &from)
    {
        to << from.getName() << " "
           << std::to_string(from.getHealth()) << " "
           << std::to_string(from.size()) << " "
           << std::to_string(from.getSex()) << " "
           << std::to_string(from.getSpeed()) << " "
           << std::to_string(from.getChanceToSurvive()) << " "
           << std::to_string(from.getCurrentStarve()) << " "
           << from.getSpritePath();

        return to;
    }

    std::string getName() { return name; }
    double getChanceToSurvive() { return chanceToSurvive; }
    virtual bool isAlive() { return fabs(random() % 10) <= (chanceToSurvive * 10 - 1); }
    virtual bool isLovely(grassEater *partner) { return this->sex != partner->sex; }
};