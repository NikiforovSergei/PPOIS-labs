#pragma once

namespace entityInterface
{
    class abstractEntity
    {
    protected:
        int health;
        unsigned int _size;

    public:
        abstractEntity(const int health, const unsigned int size)
        {
            this->health = health;
            this->_size = size;
        }
        virtual ~abstractEntity()
        {
        }

        virtual void getDamage(const int damage) { health -= damage; }
        virtual bool isDie()
        {
            if (health <= 0)
                return 1;
            else
                return 0;
        }
        unsigned int size() { return _size; }
    };

} // namespace entityInterface
