#pragma once

#include "gameState.hpp"

class autoState : public gameState::state
{
private:
    SDL_Surface *bg;
    static autoState _instance;

public:
    autoState(/* args */);
    ~autoState();

    int init();
    void cleanup();

    void pause();
    void resume();

    void events(gameEngine::engine *game);
    void update(gameEngine::engine *game);
    void draw(gameEngine::engine *game);

    static autoState *instance() { return &_instance; }
};

autoState::autoState(/* args */)
{
}

autoState::~autoState()
{
}