#pragma once

#include <memory>
#include <type_traits>

namespace gameField
{
    class field;
    class cell;
}

/**
 * @brief namespace for declaration class mainCycle
 * 
 */
namespace gameCycle
{
    /**
     * @brief declaration class mainCycle
     * 
     */
    class mainCycle
    {
    public:
        /**
         * @brief default constructor
         * 
         */
        mainCycle(/* args */)
        {
        }
        
        /**
         * @brief Destroy the main Cycle object
         * 
         */
        ~mainCycle()
        {
        }

        /**
         * @brief process of moving all entities
         * 
         * @param field 
         */
        virtual void move(gameField::field *field);
        
        /**
         * @brief process of eating entities
         * 
         * @param field 
         */
        virtual void eat(gameField::field *field);
        
        /**
         * @brief process of reproduction of entities
         * 
         * @param field 
         */
        virtual void reproduction(gameField::field *field);
        
        /**
         * @brief process of dying of entities
         * 
         * @param field 
         */
        virtual void die(gameField::field *field);
        
        /**
         * @brief moving, eating, reproduction, dying of entities
         * 
         * @param field 
         */
        virtual void nextStep(gameField::field *field);

    private:
        /**
         * @brief reproduction of animals
         * 
         * @param _cell 
         */
        void reproductionAnimals(gameField::cell *_cell);

        /**
         * @brief eating plants
         * 
         * @param tmpCell 
         */
        void eatPlants(gameField::cell *tmpCell);

        /**
         * @brief eating grassEaters
         * 
         * @param tmpCell 
         */
        void eatGrassEaters(gameField::cell *tmpCell);

        /**
         * @brief dying of animals
         * 
         * @param _cell 
         */
        void dieAnimals(gameField::cell *_cell);

        /**
         * @brief dying of grassEaters
         * 
         * @param _cell 
         */
        void dieGrassEaters(gameField::cell *_cell);

        /**
         * @brief dying of plants
         * 
         * @param _cell 
         */
        void diePlant(gameField::cell *_cell);
    };
} // namespace gameCycle
