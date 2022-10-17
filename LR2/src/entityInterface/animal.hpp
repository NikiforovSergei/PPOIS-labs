#pragma once

#include <string>
#include "abstractEntity.hpp"
#include <random>

enum sex_t
{
    MALE = 0,
    FEMALE = 1
};

/**
 * @brief declaration class animal
 * 
 */
class animal : public entityInterface::abstractEntity
{
protected:
    int starve;
    const int starveTime;
    int speed;

    sex_t sex;

public:
    /**
     * @brief Construct a new animal object
     * 
     * @param name 
     * @param health 
     * @param _size 
     * @param sex 
     * @param speed 
     * @param starveTime how long can leave without eating
     * @param spritePath 
     */
    animal(const std::string name, const int health,
           const int _size, sex_t sex,
           const int speed, const int starveTime, const std::string spritePath)
        : starveTime(starveTime), starve(starveTime), speed(speed), sex(sex),
          entityInterface::abstractEntity(name, health, _size, spritePath)
    {
        if (speed < 0 or starve <= 0)
            throw "error when construct object, type: animal";
    }
    
    /**
     * @brief Destroy the animal object
     * 
     */
    ~animal() override
    {
    }

    /**
     * @brief Get the Speed object
     * 
     * @return const int 
     */
    const int getSpeed() { return speed; }
    
    /**
     * @brief Get the Max Starve object
     * 
     * @return const int 
     */
    const int getMaxStarve() { return starveTime; }
    
    /**
     * @brief Get the Current Starve object
     * 
     * @return const int 
     */
    const int getCurrentStarve() { return starve; }
    
    /**
     * @brief Get the Sex object
     * 
     * @return const sex_t 
     */
    const sex_t getSex() { return sex; }

    /**
     * @brief move to(relative)
     * 
     * @return std::pair<const int, const int> 
     */
    virtual std::pair<const int, const int> move()
    {
        return {(random() % 3 - 1) * speed,
                (random() % 3 - 1) * speed};
    }

    /**
     * @brief overloading of operator << for animal
     * 
     * @param to 
     * @param from 
     * @return std::ostream& 
     */
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
    
    /**
     * @brief decrease starve on 1
     * 
     */
    virtual void starving() { starve -= 1; }
    
    /**
     * @brief increase starve ot max
     * 
     */
    virtual void saturation() { starve = starveTime; }

    /**
     * @brief check if animal is die
     * 
     * @return true 
     * @return false 
     */
    virtual bool isDie() override { return starve <= 0 or health <= 0; }

    /**
     * @brief check if this and partner has different sex
     * 
     * @param partner 
     * @return true 
     * @return false 
     */
    virtual bool isLovely(animal *partner) { return (this->sex != partner->sex) and (this->name == partner->name); }

private:
};
