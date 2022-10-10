#include "fieldAndCell.hpp"

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

    cell *field::getCell(const int col, const int row)
    {
        return cells.at(row).at(col);
    }

    bool field::free()
    {
        bool isError = false;
        for (int i = 0; i < cells.size(); ++i)
            for (int j = 0; j < cells.at(i).size(); ++j)
                if (!cells.at(i).at(j)->free())
                    delete cells.at(i).at(j);
                else
                    isError = true;

        printf("field is free\n");

        return isError;
    }

    void field::clear()
    {
        for (int i = 0; i < cells.size(); ++i)
            for (int j = 0; j < cells.at(i).size(); ++j)
                    cells.at(i).at(j)->clear();

        printf("field clear\n");
    }

    //*********************cell-methods*******************//

    const int cell::entityCount()
    {
        return (animals.size() + grassEaters.size() + _plant != nullptr);
    }

    void cell::clear()
    {
        _plant = nullptr;
        animals.clear();
        grassEaters.clear();
    }

    bool cell:: free()
    {
        for (auto i : animals)
        {
            delete i;
        }
        for (auto i : grassEaters)
        {
            delete i;
        }
        if (_plant != nullptr)
            delete _plant;

        clear();
        return entityCount() != 0;
    }

    bool cell::put(plant *entity)
    {
        if (entityCount() < maxEntityCount or _plant != nullptr)
        {
            if (_plant != nullptr)
                delete _plant;

            _plant = entity;
            return 0;
        }
        else
            return 1;
    }

    bool cell::put(animal *entity)
    {
        if (entityCount() < maxEntityCount)
        {
            animals.push_back(entity);
            return 0;
        }
        else
            return 1;
    }

    bool cell::put(grassEater *entity)
    {
        if (entityCount() < maxEntityCount)
        {
            grassEaters.push_back(entity);
            return 0;
        }
        else
            return 1;
    }

    void cell::del(plant *entity)
    {
        _plant = nullptr;
    }

    void cell::del(animal *entity)
    {
        for (auto i = animals.begin(); i != animals.end(); i++)
            if (*i == entity)
            {
                animals.erase(i);
                break;
            }
    }

    void cell::del(grassEater *entity)
    {
        for (auto i = grassEaters.begin(); i != grassEaters.end(); i++)
            if (*i == entity)
            {
                grassEaters.erase(i);
                break;
            }
    }
} // namespace gameField
