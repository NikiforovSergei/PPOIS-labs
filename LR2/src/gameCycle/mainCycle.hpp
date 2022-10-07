#pragma once

#include <memory>
#include <type_traits>


namespace gameField
{
    class field;
    class cell;
}

namespace gameCycle
{
    class mainCycle
    {
    public:
        mainCycle(/* args */)
        {
        }
        ~mainCycle()
        {
        }

        virtual void move(gameField::field *field);
        virtual void eat(gameField::field *field);
        virtual void reproduction(gameField::field *field);
        virtual void die(gameField::field *field);
        virtual void nextStep(gameField::field *field);

    private:
        void eatPlants(gameField::cell* tmpCell);
        void eatGrassEaters(gameField::cell* tmpCell);
    };
} // namespace gameCycle
