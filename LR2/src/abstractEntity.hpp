#pragma once

#include "fieldAndCell.hpp"

namespace entityInterface
{

    class abstractEntity
    {
    private:
        int health;
        unsigned int size;

    public:
        abstractEntity(const int health, const unsigned int size);
        virtual ~abstractEntity();

        virtual void getDamage(const unsigned int damage);
        virtual bool move(){ }
        virtual bool eat(){ }
        virtual bool reproduction(){ }
        virtual bool die(){ }

    };
    
    abstractEntity::abstractEntity(const int health, const unsigned int size)
    {

    }
    
    abstractEntity::~abstractEntity()
    {
    }
    
} // namespace entityInterface
