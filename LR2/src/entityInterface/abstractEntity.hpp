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
        size_t _size;
        std::string spritePath;

    public:
        abstractEntity(const int health, const size_t size, std::string pathToSprite)
            : health(health), _size(size), spritePath(pathToSprite)
        {}

        virtual ~abstractEntity() = default;

        virtual void getDamage(const int damage) { health -= damage; }
        virtual bool isDie()
        {
            if (health <= 0)
                return 1;
            else
                return 0;
        }
        virtual size_t size() { return _size; }
        virtual int getHealth() { return health; }
        virtual void setSpritePath(const char* path) { this->spritePath = path; }
        virtual std::string getSpritePath() { return spritePath; }
    };

} // namespace entityInterface
