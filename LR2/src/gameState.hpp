#pragma once

#include "gameEngine.hpp"

namespace gameState
{
    class state
    {
    public:
        state(/* args */);
        ~state();

        virtual void init() = 0;
        virtual void cleanup() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void events() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;

        void changeState(gameEngine::engine* game, const state* newState)
        { game->changeState(newState); }

    };
    
    state::state(/* args */)
    {
    }
    
    state::~state()
    {
    }
    
} // namespace gameState
