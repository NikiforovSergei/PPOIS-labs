#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "fieldAndCell.hpp"
#include "gameState.hpp"

namespace gameEngine
{
    class engine
    {
    private:
        std::shared_ptr<gameField::field> field;
        std::vector<gameState::state *> states;
        bool isRunning;

    public:
        SDL_Surface *screen;
        SDL_Renderer *renderer;
        SDL_Window *window;

    public:
        engine(/* args */);
        ~engine();

        int init(const char *title, const unsigned int width = 640, const unsigned int height = 480);
        void cleanup();
        void changeState(gameState::state *state);
        void pushState(gameState::state *state);
        void popState();

        void events();
        void update();
        void draw();

        bool isRun() { return isRunning; }
        void quit() { isRunning = false; }
    };

    engine::engine(/* args */)
    {
    }

    engine::~engine()
    {
    }

} // namespace gameEngine
