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
    int starve;
    const int starveTime;
    int speed;

    sex_t sex;

public:
    animal(const std::string name, const int health,
           const int _size, sex_t sex,
           const int speed, const int starveTime, const std::string spritePath)
        : starveTime(starveTime), starve(starveTime), speed(speed), sex(sex),
          entityInterface::abstractEntity(name, health, _size, spritePath)
    {
        if (speed < 0 or starve <= 0)
            throw "error when construct object, type: animal";
    }
    ~animal() override
    {
    }

    const int getSpeed() { return speed; }
    const int getMaxStarve() { return starveTime; }
    const int getCurrentStarve() { return starve; }
    const sex_t getSex() { return sex; }

    virtual std::pair<const int, const int> move()
    {
        return {(random() % 3 - 1) * speed,
                (random() % 3 - 1) * speed};
    }

    friend std::ostream &operator<<(std::ostream &to, animal &from)
    {
        to << from.getName() << " "
           << std::to_string(from.getHealth()) << " "
           << std::to_string(from.size()) << " "
           << std::to_string(from.getSex()) << " "
           << std::to_string(from.getSpeed()) << " "
           << std::to_string(from.getCurrentStarve()) << " "
           << from.getSpritePath();

        return to;
    }
    virtual void starving() { starve -= 1; }
    virtual void saturation() { starve = starveTime; }
    virtual bool isDie() override { return starve <= 0 or health <= 0; }
    virtual bool isLovely(animal *partner) { return (this->sex != partner->sex) and (this->name == partner->name); }

private:
};
