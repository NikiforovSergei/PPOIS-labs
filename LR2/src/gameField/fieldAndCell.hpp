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
        unsigned int width;
        unsigned int capacity;
        std::vector<animal *> animals;
        plant *_plant;
        std::vector<grassEater *> grassEaters;

    public:
        cell(const unsigned width, const unsigned capacity)
        {
            this->width = width;
            this->capacity = capacity;
            _plant = nullptr;
        }

        ~cell()
        {
            clear();
        }

        const unsigned int freeUnitsNum();
        const unsigned int entityCount();

        template <typename T>
        requires std::is_same_v<T, plant *>
        bool put(T entity);

        template <typename T>
        requires std::is_same_v<T, animal *>
        bool put(T entity);

        template <typename T>
        requires std::is_same_v<T, grassEater *>
        bool put(T entity);

        template <typename T>
        requires std::is_same_v<T, plant *>
        void del(T entity);

        template <typename T>
        requires std::is_same_v<T, animal *> or std::is_same_v<T, grassEater *>
        void del(T entity);

        template <typename T>
        requires std::is_same_v<T, plant>
            plant *get() { return _plant; }

        template <typename T>
        requires std::is_same_v<T, animal>
            std::vector<animal *> get() { return animals; }

        template <typename T>
        requires std::is_same_v<T, grassEater>
            std::vector<grassEater *> get() { return grassEaters; }

        bool clear();
    };

    template <typename T>
    requires std::is_same_v<T, plant *>
    bool cell::put(T entity)
    {
        if ((entityCount() < 4 and freeUnitsNum() >= entity.size()) or _plant != nullptr)
        {
            if (_plant != nullptr)
                delete _plant;

            _plant = entity;
            return 0;
        }
        else
            return 1;
    }

    template <typename T>
    requires std::is_same_v<T, animal *>
    bool cell::put(T entity)
    {
        if ((entityCount() < 4) and (freeUnitsNum() >= entity->size()))
        {
            animals.push_back(entity);
            return 0;
        }
        else
            return 1;
    }

    template <typename T>
    requires std::is_same_v<T, grassEater *>
    bool cell::put(T entity)
    {
        if (entityCount() < 4 and freeUnitsNum() >= entity->size())
        {
            grassEaters.push_back(entity);
            return 0;
        }
        else
            return 1;
    }

    template <typename T>
    requires std::is_same_v<T, plant *>
    void cell::del(T entity)
    {
        _plant = nullptr;
    }

    template <typename T>
    requires std::is_same_v<T, animal *> || std::is_same_v<T, grassEater *>
    void cell::del(T entity)
    {
        if (std::is_same_v<T, animal *>)
        {
            for (auto i = animals.begin(); i != animals.end(); i++)
            {
                if (*i == entity)
                    animals.erase(i);
                break;
            }
        }
        else
        {
            for (auto i = grassEaters.begin(); i != grassEaters.end(); i++)
            {
                if (*i == entity)
                    grassEaters.erase(i);
                break;
            }
        }
    }

    /*-------------------------------------------------------------*/

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
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                    tempRow.push_back(new cell(40, 100));
                cells.push_back(tempRow);
                tempRow.clear();
            }
        }

        ~field()
        {
            clear();
        }

        std::pair<const unsigned int, const unsigned int> size()
        {
            return {width, height};
        }

        friend std::istream &operator>>(std::istream &from, field &to);

        friend std::ostream &operator<<(std::ostream &to, const field &from);

        cell *getCell(const unsigned int row, const unsigned col);
        bool clear();
    };

} // namespace gameField
