#pragma once

#include <SDL2/SDL.h>
#include "gameState.hpp"

namespace gameEngine
{
    class engine;
}

class autoState : public gameState::state
{
private:
    SDL_Surface * bg;

public:
    autoState(/* args */)
    {
    }
    ~autoState() override
    {
        cleanup();
    }

    int init() override;
    void cleanup() override;

    void pause() override;
    void resume() override;

    void events(gameEngine::engine * game) override;
    void update(gameEngine::engine * game) override;
    void draw(gameEngine::engine * game) override;
};