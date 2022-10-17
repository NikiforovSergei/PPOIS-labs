#pragma once

#include "abstractEntity.hpp"

/**
 * @brief declaration of class plant
 * 
 */
class plant : public entityInterface::abstractEntity
{
protected:
    /* data */
public:
    /**
     * @brief Construct a new plant object
     * 
     * @param name 
     * @param health 
     * @param spritePath 
     */
    plant(const std::string name, const int health,
          const std::string spritePath)
        : abstractEntity(name, health, 50, spritePath)
    {
        if (health <= 0)
            throw "error when conctruct object, type: plant";
    }
    
    /**
     * @brief Construct a new plant object
     * 
     * @param other 
     */
    plant(const plant &other)
        : abstractEntity(other.name, other.health, other.maxHealth, other.spritePath)
    {
    }

    /**
     * @brief overloading of operator << for plant
     * 
     * @param to 
     * @param from 
     * @return std::ostream& 
     */
    friend std::ostream &operator<<(std::ostream &to, plant &from)
    {
        to << from.getName() << " "
           << std::to_string(from.getHealth()) << " "
           << from.getSpritePath();

        return to;
    }

    /**
     * @brief Destroy the plant object
     * 
     */
    ~plant() override
    {
    }
};