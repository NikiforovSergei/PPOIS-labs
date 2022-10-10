#pragma once

#include <vector>
#include <fstream>
#include <memory>
#include <type_traits>
#include <concepts>

#include "../entityInterface/plant.hpp"
#include "../entityInterface/animal.hpp"
#include "../entityInterface/grassEater.hpp"

namespace gameField
{

    class cell
    {
    protected:
        std::vector<animal *> animals;
        std::vector<grassEater *> grassEaters;
        plant *_plant;
        int maxEntityCount;

    public:
        cell(const int maxEntityCount)
            : maxEntityCount(maxEntityCount), _plant(nullptr)
        {
        }

        cell(const cell &from)
        {
            for (auto i : from.animals)
                if (i)
                    animals.push_back(new animal(*i));

            for (auto i : from.grassEaters)
                if (i)
                    grassEaters.push_back(new grassEater(*i));

            if (from._plant != nullptr)
                _plant = new plant(*from._plant);
            else
                _plant = nullptr;

            maxEntityCount = from.maxEntityCount;
        }

        ~cell()
        {
            free();
        }

        const int entityCount();

        bool put(plant *entity);
        bool put(animal *entity);
        bool put(grassEater *entity);

        void del(plant *entity);
        void del(animal *entity);
        void del(grassEater *entity);

        template <typename T>
        requires std::is_same_v<T, plant>
            plant *get() { return _plant; }

        template <typename T>
        requires std::is_same_v<T, animal>
            std::vector<animal *> get() { return animals; }

        template <typename T>
        requires std::is_same_v<T, grassEater>
            std::vector<grassEater *> get() { return grassEaters; }

        void clear();
        bool free();
    };

    /*-------------------------------------------------------------*/

    class field
    {
    private:
        std::vector<std::vector<cell *>> cells;
        int width;
        int height;

    public:
        field(const uint width, const uint height, const cell &exampleCell)
            : width(width), height(height)
        {
            std::vector<cell *> tempRow;
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                    tempRow.push_back(new cell(exampleCell));
                cells.push_back(tempRow);
                tempRow.clear();
            }
        }

        field(const field &from)
        {
            std::vector<cell *> tempRow;
            for (size_t i = 0; i < from.cells.size(); ++i)
            {
                for (size_t j = 0; j < from.cells.at(i).size(); ++j)
                    tempRow.push_back(new cell(*from.cells.at(i).at(j)));
                cells.push_back(tempRow);
                tempRow.clear();
            }
            width = from.width;
            height = from.height;
        }

        field &operator=(const field &other)
        {
            if (this != &other)
            {
                free();
                cells.clear();
                std::vector<cell *> tempRow;
                for (size_t i = 0; i < other.cells.size(); ++i)
                {
                    for (size_t j = 0; j < other.cells.at(i).size(); ++j)
                        tempRow.push_back(new cell(*other.cells.at(i).at(j)));
                    cells.push_back(tempRow);
                    tempRow.clear();
                }
                width = other.width;
                height = other.height;
            }
            return *this;
        }

        ~field()
        {
            free();
        }

        std::pair<const int, const int> size()
        {
            return {width, height};
        }

        friend std::istream &operator>>(std::istream &from, field &to);

        friend std::ostream &operator<<(std::ostream &to, const field &from);

        cell *getCell(const int row, const int col);
        void clear();
        bool free();
    };

} // namespace gameField
