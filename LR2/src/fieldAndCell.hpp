#pragma once
#include<vector>
#include<fstream>
#include<memory>

#include "abstractEntity.hpp"

namespace gameField
{

    class cell
    {
    private:
        unsigned int width;
        unsigned int capacity;
        std::vector<std::shared_ptr<entityInterface::abstractEntity>> entities;

    public:
        cell(const unsigned width, const unsigned capacity);
        ~cell();

        unsigned int freeUnitsNum();
        bool put(const entityInterface::abstractEntity* entity);
        bool del(const entityInterface::abstractEntity* entity);
        bool clear();

    };
    
    cell::cell(const unsigned width, const unsigned capacity)
    {
        this->width = width;
        this->capacity = capacity;
    }
    
    cell::~cell()
    {
        clear();
    }
    
    class field
    {
    private:
        std::vector<std::vector<cell>> cells;
        unsigned int width;
        unsigned int height;

    public:
        field(const unsigned int width, const unsigned int height);
        field(const field& from);
        ~field();

        friend
        std::istream& operator>>(std::istream& from, field& to);

        friend
        std::ostream& operator<<(std::ostream& to, const field& from);

        cell getCell(const unsigned int row, const unsigned col);
        bool clear();

    };
    
    field::field(const unsigned int width, const unsigned int height)
    {
        this->width = width;
        this->height = height;
    }
    
    field::field(const field& from)
    {
        *this = from;
    }

    field::~field()
    {
        clear();
    }
    
} // namespace gameField
