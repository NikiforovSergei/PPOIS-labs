#pragma once

#include "gameState.hpp"

class introState : public gameState::state
{
private:
    SDL_Surface *bg;
    static introState _instance;

public:
    introState(/* args */);
    ~introState();

    int init();
    void cleanup();

    void pause();
    void resume();

    void events(gameEngine::engine *game);
    void update(gameEngine::engine *game);
    void draw(gameEngine::engine *game);

    static introState *instance() { return &_instance; }
};

introState::introState(/* args */)
{
}

introState::~introState()
{
}