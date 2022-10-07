#include "fieldAndCell.hpp"
#include "../entityInterface/abstractEntity.hpp"

namespace gameField
{
    //*********************Field-methods*******************//
    std::istream &operator>>(std::istream &from, field &to)
    {
        return from;
    }

    std::ostream &operator<<(std::ostream &to, field &from)
    {
        return to;
    }

    cell *field::getCell(const unsigned int col, const unsigned row)
    {
        return cells.at(row).at(col);
    }

    bool field::clear()
    {
        bool isError = false;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (!cells.at(i).at(j)->clear())
                    delete cells.at(i).at(j);
                else
                    isError = true;
        cells.clear();

        printf("field clear\n");

        return isError;
    }

    //*********************cell-methods*******************//

    const unsigned int cell::freeUnitsNum()
    {
        int ret = capacity;
        for (int i = 0; i < grassEaters.size(); i++)
            ret -= grassEaters.at(i)->size();

        for (size_t i = 0; i < animals.size(); i++)
            ret -= animals.at(i)->size();

        if (_plant != nullptr)
            ret -= _plant->size();

        if (ret < 0)
            throw "capacity < 0";
        else
            return ret;
    }

    const unsigned int cell::entityCount()
    {
        return (animals.size() + grassEaters.size() + _plant != nullptr);
    }

    bool cell::clear()
    {
        for (size_t i = 0; i < animals.size(); i++)
        {
            delete animals.at(i);
        }
        for (size_t i = 0; i < grassEaters.size(); i++)
        {
            delete grassEaters.at(i);
        }
        if (_plant != nullptr)
            delete _plant;
        animals.clear();
        grassEaters.clear();
        _plant = nullptr;

        return freeUnitsNum() == capacity;
    }
} // namespace gameField
