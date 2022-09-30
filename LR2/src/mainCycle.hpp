#pragma once

namespace gameCycle
{
    class mainCycle
    {
    private:
        /* data */
    public:
        mainCycle(/* args */);
        ~mainCycle();

        void move();
        void eat();
        void reproduction();
        void die();
        void nextStep();
         
    };
    
    mainCycle::mainCycle(/* args */)
    {
    }
    
    mainCycle::~mainCycle()
    {
    }
    
} // namespace gameCycle
