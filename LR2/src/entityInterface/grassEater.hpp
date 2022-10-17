#pragma once

#include <string>
#include "animal.hpp"
#include <random>

/**
 * @brief declaration of class grassEater
 * 
 */
class grassEater : public animal
{
protected:
    double chanceToSurvive;

public:
    /**
     * @brief Construct a new grass Eater object
     * 
     * @param name 
     * @param health 
     * @param _size 
     * @param sex 
     * @param speed 
     * @param _chanceToSurvive 
     * @param starveTime 
     * @param spritePath 
     */
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
    
    /**
     * @brief Destroy the grass Eater object
     * 
     */
    ~grassEater() override
    {
    }

    /**
     * @brief overloading of operator << for grassEater
     * 
     * @param to 
     * @param from 
     * @return std::ostream& 
     */
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

    /**
     * @brief Get the Name object
     * 
     * @return std::string 
     */
    std::string getName() { return name; }

    /**
     * @brief Get the Chance To Survive object
     * 
     * @return double 
     */
    double getChanceToSurvive() { return chanceToSurvive; }

    /**
     * @brief check if grassEater if alive
     * 
     * @return true 
     * @return false 
     */
    virtual bool isAlive() { return fabs(random() % 10) <= (chanceToSurvive * 10 - 1); }

    /**
     * @brief check if this and partner has different sex
     * 
     * @param partner 
     * @return true 
     * @return false 
     */
    virtual bool isLovely(grassEater *partner) { return this->sex != partner->sex; }
};