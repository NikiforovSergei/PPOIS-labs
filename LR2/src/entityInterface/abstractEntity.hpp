//#pragma once

namespace entityInterface
{
    class abstractEntity
    {
    private:
        int health;
        unsigned int _size;

    public:
        abstractEntity(const int health, const unsigned int size);
        virtual ~abstractEntity();

        virtual void getDamage() = 0;
        virtual bool move(){ return 0; }
        virtual bool eat(){ return 0; }
        virtual bool reproduction(){ return 0; }
        virtual bool die(){ return 0; }
        unsigned int size(){ return _size; }

    };
    
    abstractEntity::abstractEntity(const int health, const unsigned int size)
    {
        this->health = health;
        this->_size = size;
    }
    
    abstractEntity::~abstractEntity()
    {
    }
} // namespace entityInterface
