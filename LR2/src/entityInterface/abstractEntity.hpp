#pragma once

#include <SDL2/SDL_image.h>
#include <fstream>
#include <string>

namespace entityInterface
{
    class abstractEntity
    {
    protected:
        int health;
        int maxHealth;
        size_t _size;
        std::string spritePath;
        std::string name;

    public:
        abstractEntity(std::string name, const int health,
                       const size_t size, std::string pathToSprite)
            : name(name), health(health), maxHealth(health), _size(size), spritePath(pathToSprite)
        {
            if (maxHealth <= 0 or _size < 0)
                throw "error when construct object, type: abstractEntity";
        }

        virtual ~abstractEntity() = default;

        virtual void getDamage(const int damage) { health -= damage; }
        virtual bool isDie()
        {
            if (health <= 0)
                return 1;
            else
                return 0;
        }

        std::string getName() { return name; }
        virtual size_t size() { return _size; }
        virtual int getHealth() { return health; }
        virtual int getMaxHealth() { return maxHealth; }
        virtual void setSpritePath(const char *path) { this->spritePath = path; }
        virtual std::string getSpritePath() { return spritePath; }
    };

} // namespace entityInterface
