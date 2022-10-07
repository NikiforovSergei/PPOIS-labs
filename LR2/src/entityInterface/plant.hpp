#pragma once

#include "abstractEntity.hpp"

class plant : public entityInterface::abstractEntity
{
protected:
    /* data */
public:
    plant(const int health) : abstractEntity(health, 50)
    {
    }
    ~plant();
};
