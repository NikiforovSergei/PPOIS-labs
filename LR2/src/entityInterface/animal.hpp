#pragma once

#include <string>
#include "abstractEntity.hpp"
#include <random>

enum sex_t
{
    MALE = 0,
    FEMALE = 1
};

class animal : public entityInterface::abstractEntity
{
protected:
    std::string name;
    int starve;
    uint speed;

    sex_t sex;

public:
    animal(const std::string name, const int health,
           const uint _size, sex_t sex,
           const uint speed = 1, const char *spritePath = nullptr)
        : name(name), starve(5), speed(speed), sex(sex), entityInterface::abstractEntity(health, _size, spritePath)
    {
    }
    ~animal() override
    {
    }

    std::string getName() { return name; }
    uint getSpeed() { return speed; }

    virtual std::pair<const int, const int> move()
    {
        return {(random() % 3 - 1) * speed,
               (random() % 3 - 1) * speed};
    }

    virtual void starving() { starve -= 1; }
    virtual void saturation() { starve = 5; }
    virtual bool isDie() override { return starve <= 0 or health <= 0; }
    virtual bool isLovely(animal *partner) { return (this->sex != partner->sex) and (this->name == partner->name); }

private:
};
