#pragma once

#include <SDL2/SDL.h>

namespace gameEngine { class engine; }
#include "gameState.hpp"

class introState : public gameState::state
{
private:
    SDL_Surface *bg;

public:
    introState(/* args */);
    ~introState() override;

    int init() override;
    void cleanup() override;

    void pause() override;
    void resume() override;

    void events(gameEngine::engine *game) override;
    void update(gameEngine::engine *game) override;
    void draw(gameEngine::engine *game) override;
};

introState::introState(/* args */)
{
}

introState::~introState()
{
    cleanup();
}