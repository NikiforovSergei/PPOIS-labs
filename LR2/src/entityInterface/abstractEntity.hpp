#pragma once

#include <SDL2/SDL_image.h>
#include <fstream>
#include <string>

/**
 * @brief namespace for declaration class abstractEntity
 * 
 */
namespace entityInterface
{
    /**
     * @brief abstract class of entity
     * 
     */
    class abstractEntity
    {
    protected:
        int health;
        int maxHealth;
        size_t _size;
        std::string spritePath;
        std::string name;

    public:
        /**
         * @brief Construct a new abstract Entity object
         * 
         * @param name 
         * @param health 
         * @param size 
         * @param pathToSprite 
         */
        abstractEntity(std::string name, const int health,
                       const size_t size, std::string pathToSprite)
            : name(name), health(health), maxHealth(health), _size(size), spritePath(pathToSprite)
        {
            if (maxHealth <= 0 or _size < 0)
                throw "error when construct object, type: abstractEntity";
        }

        /**
         * @brief Destroy the abstract Entity object
         * 
         */
        virtual ~abstractEntity() = default;

        /**
         * @brief Get the Damage object
         * 
         * @param damage 
         */
        virtual void getDamage(const int damage) { health -= damage; }
        
        /**
         * @brief check if entity is die
         * 
         * @return true 
         * @return false 
         */
        virtual bool isDie()
        {
            if (health <= 0)
                return 1;
            else
                return 0;
        }

        /**
         * @brief Get the Name object
         * 
         * @return std::string 
         */
        std::string getName() { return name; }
        
        /**
         * @brief get size of entity
         * 
         * @return size_t 
         */
        virtual size_t size() { return _size; }
        
        /**
         * @brief Get the Health object
         * 
         * @return int 
         */
        virtual int getHealth() { return health; }
        
        /**
         * @brief Get the Max Health object
         * 
         * @return int 
         */
        virtual int getMaxHealth() { return maxHealth; }
        
        /**
         * @brief Set the Sprite Path object
         * 
         * @param path 
         */
        virtual void setSpritePath(const char *path) { this->spritePath = path; }
        
        /**
         * @brief Get the Sprite Path object
         * 
         * @return std::string 
         */
        virtual std::string getSpritePath() { return spritePath; }
    };

} // namespace entityInterface
