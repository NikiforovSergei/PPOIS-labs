#pragma once

namespace gameField
{
    class field;
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

        void move();
        void eat();
        void reproduction();
        void die();
        void nextStep(gameField::field *field){}
    };

} // namespace gameCycle
