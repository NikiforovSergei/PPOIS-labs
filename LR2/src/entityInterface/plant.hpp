#pragma once

#include "abstractEntity.hpp"

class plant : public entityInterface::abstractEntity
{
protected:
    /* data */
public:
    plant(const int health, const char *spritePath = nullptr) : abstractEntity(health, 50, spritePath)
    {
    }
    ~plant() override
    {
    }
};
