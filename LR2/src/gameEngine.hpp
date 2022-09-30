#pragma once

#include<SDL2/SDL.h>
#include "fieldAndCell.hpp"
#include "gameState.hpp"

namespace gameEngine
{
   class engine
    {
    private:
        std::shared_ptr<gameField::field> field;
        std::vector<gameState::state*> states;
        bool isRun;

        SDL_Surface* screen;

    public:
        engine(/* args */);
        ~engine();

        void init(const char* title, const unsigned int width=640, const unsigned int height=480);
        void cleanup();
        void changeState(const gameState::state* state);
        void pushState(const gameState::state* state);
        void popState();

        void events();
        void update();
        void draw();

        bool isRun(){ return isRun; }
        void quit(){ isRun = false; }

    };
    
    engine::engine(/* args */)
    {
    }
    
    engine::~engine()
    {
    }

} // namespace gameEngine
