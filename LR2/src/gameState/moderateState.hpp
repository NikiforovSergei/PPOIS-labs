#pragma once

#include <SDL2/SDL.h>

namespace gameEngine { class engine; }
#include "gameState.hpp"

class moderateState : public gameState::state
{
private:
    SDL_Surface *bg;

public:
    moderateState(/* args */);
    ~moderateState() override;

    int init() override;
    void cleanup() override;

    void pause() override;
    void resume() override;

    void events(gameEngine::engine *game) override;
    void update(gameEngine::engine *game) override;
    void draw(gameEngine::engine *game) override;
};

moderateState::moderateState(/* args */)
{
}

moderateState::~moderateState()
{
    cleanup();
}
