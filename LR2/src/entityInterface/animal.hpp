#pragma once

#include <string>
#include "abstractEntity.hpp"

enum sex_t
{
    MALE,
    FEMALE
};

class animal : public entityInterface::abstractEntity
{
protected:
    unsigned int speed;
    unsigned int stepsLeft;
    int starve;
    std::string name;

    sex_t sex;

public:
    animal(const std::string name, const int health,
           const unsigned int _size, sex_t sex,
           const unsigned int stepsLeft, const unsigned int speed = 1)
        : entityInterface::abstractEntity(health, _size)
    {
        this->name = name;
        this->stepsLeft = stepsLeft;
        this->speed = speed;
        this->sex = sex;
        this->starve = 5;
    }
    ~animal()
    {
    }

    std::string getName() { return name; }
    std::pair<const int, const int> move();
    void starving() { starve -= 1; }
    void saturation() { starve = 5; }
    virtual bool isDie() override { return starve <= 0 or health <= 0; }
    virtual bool isLovely(animal* partner) { return this->sex != partner->sex; }
private:

};
