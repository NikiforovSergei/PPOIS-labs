#pragma once

#include <vector>
#include <fstream>
#include <memory>

namespace entityInterface
{
    class abstractEntity;
}

namespace gameField
{

    class cell
    {
    private:
        unsigned int width;
        unsigned int capacity;
        std::vector<entityInterface::abstractEntity *> entities;

    public:
        cell(const unsigned width, const unsigned capacity)
        {
            this->width = width;
            this->capacity = capacity;
        }

        ~cell()
        {
            clear();
        }

        unsigned int freeUnitsNum();
        bool put(entityInterface::abstractEntity *entity);
        bool del(entityInterface::abstractEntity *entity);
        bool clear();
    };

    //    cell::cell(const unsigned width, const unsigned capacity)
    //   cell::~cell()

    class field
    {
    private:
        std::vector<std::vector<cell *>> cells;
        unsigned int width;
        unsigned int height;

    public:
        field(const unsigned int width, const unsigned int height)
        {
            this->width = width;
            this->height = height;
            std::vector<cell *> tempRow;
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                    tempRow.push_back(new cell(40, 30));
                cells.push_back(tempRow);
            }
        }

        field(const field &from) = delete;
        field(const field &&from) = delete;

        ~field()
        {
            clear();
        }

        friend std::istream &operator>>(std::istream &from, field &to);

        friend std::ostream &operator<<(std::ostream &to, const field &from);

        cell *getCell(const unsigned int row, const unsigned col);
        bool clear();
    };

} // namespace gameField
