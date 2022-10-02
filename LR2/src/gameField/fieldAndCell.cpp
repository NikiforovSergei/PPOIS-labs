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

    cell *field::getCell(const unsigned int row, const unsigned col)
    {
        return cells[row][col];
    }

    bool field::clear()
    {
        bool isError = false;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (!cells[i][j]->clear())
                    delete cells[i][j];
                else
                    isError = true;

        return isError;
    }

    //*********************cell-methods*******************//

    unsigned int cell::freeUnitsNum()
    {
        unsigned int ret = capacity;
        for (int i = 0; i < entities.size(); i++)
            ret -= entities[i]->size();

        return ret;
    }

    bool cell::put(entityInterface::abstractEntity *entity)
    {
        if (entities.size() < 4)
        {
            entities.push_back(entity);
            return 0;
        }
        else
            return 1;
    }

    bool cell::del(entityInterface::abstractEntity *entity)
    {
        for (auto i = 0; i < entities.size(); i++)
            if (entities[i] == entity)
            {
                delete entities[i];
                entities.erase(entities.begin() + i);
                return 0;
            }
        return 1;
    }

    bool cell::clear()
    {
        for (size_t i = entities.size(); i > 0; i--)
        {
            delete entities[i];
            entities.pop_back();
        }

        return !entities.empty();
    }
} // namespace gameField
