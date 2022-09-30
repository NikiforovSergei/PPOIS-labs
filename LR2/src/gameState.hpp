#pragma once

#include "gameEngine.hpp"

namespace gameState
{
    class state
    {
    public:
        state(/* args */);
        ~state();

        virtual int init() = 0;
        virtual void cleanup() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void events(gameEngine::engine *game) = 0;
        virtual void update(gameEngine::engine *game) = 0;
        virtual void draw(gameEngine::engine *game) = 0;

        void changeState(gameEngine::engine *game, state *newState)
        {
            game->changeState(newState);
        }
    };

    state::state(/* args */)
    {
    }

    state::~state()
    {
    }

} // namespace gameState
