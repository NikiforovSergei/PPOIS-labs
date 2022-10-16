#include "fieldAndCell.hpp"
#include "../extraFuncs.cpp"
#include "../entityInterface/animal.hpp"
#include "../entityInterface/plant.hpp"
#include "../entityInterface/grassEater.hpp"

#include <string>
#include <vector>
#include <algorithm>

namespace gameField
{
    //*********************Field-methods*******************//

    void strToEntity(std::vector<animal *> &animals,
                     std::vector<grassEater *> &grassEaters,
                     std::vector<plant *> &plants,
                     std::vector<std::string> entityDescription)
    {
        if (entityDescription.at(0) == "animal")
        {
            animals.push_back(new animal(
                entityDescription.at(1),                      // name
                atoi(entityDescription.at(2).c_str()),        // health
                atoi(entityDescription.at(3).c_str()),        // size
                (sex_t)atoi(entityDescription.at(4).c_str()), // sex
                atoi(entityDescription.at(5).c_str()),        // speed
                atoi(entityDescription.at(6).c_str()),        // starveTime
                entityDescription.at(7)));                    // spritePath
        }
        else if (entityDescription.at(0) == "grassEater")
        {
            grassEaters.push_back(new grassEater(
                entityDescription.at(1),
                atoi(entityDescription.at(2).c_str()),
                atoi(entityDescription.at(3).c_str()),
                (sex_t)atoi(entityDescription.at(4).c_str()),
                atoi(entityDescription.at(5).c_str()),
                atof(entityDescription.at(6).c_str()), // chanceToSurvive
                atoi(entityDescription.at(7).c_str()),
                entityDescription.at(8)));
        }
        else if (entityDescription.at(0) == "plant")
        {
            plants.push_back(new plant(
                entityDescription.at(1),
                atoi(entityDescription.at(2).c_str()),
                entityDescription.at(3)));
        }
    }

    std::istream &operator>>(std::istream &from, field &to)
    {
        std::string line;
        std::vector<animal *> animals;
        std::vector<grassEater *> grassEaters;
        std::vector<plant *> plants;
        gameField::cell *_templateCell = nullptr;

        while (getline(from, line))
        {
            std::vector<std::string> tmp = split(line, " "); // entity description in vector
            leftTrim(line, " ");
            if (tmp.empty())
                continue;

            else if (line.at(0) == '#')
                continue;

            else if (tmp.at(0) == "animal" or
                     tmp.at(0) == "grassEater" or
                     tmp.at(0) == "plant")
                strToEntity(animals, grassEaters, plants, tmp);

            else if (tmp.at(0) == "templateCell")
                _templateCell = new gameField::cell(atoi(tmp.at(1).c_str()));

            else if (tmp.at(0) == "field" and _templateCell != nullptr)
                to = gameField::field(
                    atoi(tmp.at(1).c_str()), // width
                    atoi(tmp.at(2).c_str()), // height
                    *_templateCell);

            else if (tmp.at(0) == "cell")
            {
                gameField::cell *tmpCell = to.getCell(
                    atoi(tmp.at(1).c_str()), // col
                    atoi(tmp.at(2).c_str())  // row
                );

                for (int i = 3; i < tmp.size(); ++i)
                {
                    bool isPut = false;
                    if (tmp.at(i).find("-") != std::string::npos)
                    {
                        for (auto j : animals)
                            if ((sex_t)atoi(split(tmp.at(i), "-").at(1).c_str()) == j->getSex())
                                if (!tmpCell->fillCellByName(split(tmp.at(i), "-").at(0), j))
                                {
                                    isPut = true;
                                    break;
                                }
                        if (isPut)
                            continue;

                        for (auto j : grassEaters)
                            if ((sex_t)atoi(split(tmp.at(i), "-").at(1).c_str()) == j->getSex())
                                if (!tmpCell->fillCellByName(split(tmp.at(i), "-").at(0), j))
                                {
                                    isPut = true;
                                    break;
                                }
                        if (isPut)
                            continue;
                    }
                    else
                    {
                        for (auto j : plants)
                            if (!tmpCell->fillCellByName(tmp.at(i), j))
                                break;
                    }
                }

                line.clear();
            }
        }
        return from;
    }

    void printEntitiesInCell(std::ostream &to, cell *_cell)
    {
        for (auto _animal : _cell->get<animal>())
            to << " " << _animal->getName() << "-" << _animal->getSex();

        for (auto _grassEater : _cell->get<grassEater>())
            to << " " << _grassEater->getName() << "-" << _grassEater->getSex();

        auto _plant = _cell->get<plant>();
        if (_plant != nullptr)
            to << " " << _plant->getName();
    }

    void printEntities(std::ostream &to, cell *_cell)
    {
        std::string entity;
        std::vector<std::string> entities;
        for (auto _animal : _cell->get<animal>())
            to << *_animal << std::endl;

        for (auto _grassEater : _cell->get<grassEater>())
            to << *_grassEater << std::endl;

        auto _plant = _cell->get<plant>();
        if (_plant != nullptr)
            to << *_plant << std::endl;
    }

    std::ostream &operator<<(std::ostream &to, const field &from)
    {
        std::string line;

        if (from.size().second == 0 or from.size().first == 0)
            return to;

        for (int i = 0; i < from.size().first; ++i)
            for (int j = 0; j < from.size().second; ++j)
            {
                printEntities(to, from.getCell(i, j));
            }

        to << "templateCell " << from.getCell(0, 0)->getMaxEntityCount() << std::endl;

        to << "field " << from.size().first << " " << from.size().second << std::endl;

        for (int i = 0; i < from.size().first; ++i)
            for (int j = 0; j < from.size().second; ++j)
            {
                to << "cell " << i << " " << j;
                printEntitiesInCell(to, from.getCell(i, j));
                to << std::endl;
            }

        return to;
    }

    cell *field::getCell(const int col, const int row) const
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

    bool cell::free()
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
