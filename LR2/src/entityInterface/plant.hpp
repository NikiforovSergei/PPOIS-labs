#pragma once

#include "abstractEntity.hpp"

class plant : public entityInterface::abstractEntity
{
protected:
    /* data */
public:
    plant(const std::string name, const int health,
          const std::string spritePath)
        : abstractEntity(name, health, 50, spritePath)
    {
        if (health <= 0)
            throw "error when conctruct object, type: plant";
    }
    plant(const plant &other)
        : abstractEntity(other.name, other.health, other.maxHealth, other.spritePath)
    {
    }

    friend std::ostream &operator<<(std::ostream &to, plant &from)
    {
        to << from.getName() << " "
           << std::to_string(from.getHealth()) << " "
           << from.getSpritePath();

        return to;
    }

    ~plant() override
    {
    }
};