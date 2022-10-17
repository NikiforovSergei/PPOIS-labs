#pragma once

#include <vector>
#include <fstream>
#include <memory>
#include <type_traits>
#include <concepts>

#include "../entityInterface/plant.hpp"
#include "../entityInterface/animal.hpp"
#include "../entityInterface/grassEater.hpp"

/**
 * @brief namespace for declaration class field and cell
 * 
 */
namespace gameField
{

    /**
     * @brief class cell, each element can contane different entities
     * 
     */
    class cell
    {
    protected:
        std::vector<animal *> animals;
        std::vector<grassEater *> grassEaters;
        plant *_plant;
        int maxEntityCount;

    public:
        /**
         * @brief Construct a new cell object
         * 
         * @param maxEntityCount
         */
        cell(const int maxEntityCount)
            : maxEntityCount(maxEntityCount), _plant(nullptr)
        {
            if (maxEntityCount < 0)
                throw "error when construct object, type: gameField::field";
        }

        /**
         * @brief Construct a new cell object
         * 
         * @param from template to create cell
         */
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

        /**
         * @brief Destroy the cell object
         * 
         */
        ~cell()
        {
            free();
        }

        /**
         * @brief find number of entities in the cell
         * 
         * @return const int number of entities
         */
        const int entityCount();

        /**
         * @brief put entity to cell
         * 
         * @param entity what put to cell
         * @return true if failure put
         * @return false if success
         */
        bool put(plant *entity);
        bool put(animal *entity);
        bool put(grassEater *entity);

        /**
         * @brief erase entity from cell(whithout free storage)
         * 
         * @param entity what to erase
         */
        void del(plant *entity);
        void del(animal *entity);
        void del(grassEater *entity);

        /**
         * @brief get plant from cell
         * 
         * @tparam T animal, grassEater, or plant
         * @return requires* 
         */
        template <typename T>
        requires std::is_same_v<T, plant>
            plant *get() { return _plant; }

        /**
         * @brief get vector of animals in cell
         * 
         * @tparam T animal, grassEater, or plant
         * @return requires 
         */
        template <typename T>
        requires std::is_same_v<T, animal>
            std::vector<animal *> get() { return animals; }

        /**
         * @brief get vector of grassEater in cell
         * 
         * @tparam T animal, grassEater, or plant
         * @return requires 
         */
        template <typename T>
        requires std::is_same_v<T, grassEater>
            std::vector<grassEater *> get() { return grassEaters; }

        /**
         * @brief Get the Max Entity Count object
         * 
         * @return const int 
         */
        const int getMaxEntityCount(){ return maxEntityCount; }

        /**
         * @brief fill cell with entity if entity->name == name
         * 
         * @tparam T 
         * @param name 
         * @param entity 
         * @return true 
         * @return false 
         */
        template <typename T>
        bool fillCellByName(const std::string name, T *entity);

        /**
         * @brief clear all entities in cell
         * 
         */
        void clear();
        
        /**
         * @brief free storage of entities in cell
         * 
         * @return true if failure
         * @return false if success
         */
        bool free();
    };

    template <typename T>
    bool cell::fillCellByName(const std::string name, T *entity)
    {
        if (name == entity->getName())
        {
            put(new T(*entity));
            return 0;
        }

        return 1;
    }

    /* -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -*/

    class field
    {
    private:
        std::vector<std::vector<cell *>> cells;
        int width;
        int height;

    public:
        field() {}

        field(const int width, const int height, const cell &exampleCell)
            : width(width), height(height)
        {
            if (width < 0 or height < 0)
                throw "error when construct object, type: gameField::field";

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

        std::pair<const int, const int> size() const
        {
            return {width, height};
        }

        friend std::istream &operator>>(std::istream &from, field &to);

        friend std::ostream &operator<<(std::ostream &to, const field &from);

        cell *getCell(const int row, const int col) const;
        void clear();
        bool free();
    };

} // namespace gameField
