#pragma ocne

#include "gameState.hpp"

class moderateState : public gameState::state
{
private:
    SDL_Surface *bg;
    static moderateState _instance;

public:
    moderateState(/* args */);
    ~moderateState();

    int init();
    void cleanup();

    void pause();
    void resume();

    void events(gameEngine::engine *game);
    void update(gameEngine::engine *game);
    void draw(gameEngine::engine *game);

    static moderateState *instance() { return &_instance; }
};

moderateState::moderateState(/* args */)
{
}

moderateState::~moderateState()
{
}