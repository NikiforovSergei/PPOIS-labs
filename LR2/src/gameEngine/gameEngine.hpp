#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <memory>

namespace gameState
{
    class state;
}
namespace gameField
{
    class field;
}
namespace gameCycle
{
    class mainCycle;
}

namespace gameEngine
{
    class engine
    {
    private:
        std::vector<gameState::state *> states;
        bool isRunning;

    public:
        gameField::field *field;
        gameCycle::mainCycle *cycle;
        SDL_Surface *screen;
        SDL_Renderer *renderer;
        SDL_Window *window;

    public:
        engine(gameField::field* _field, gameCycle::mainCycle* _cycle)
        {
            states = {};
            isRunning = false;
            field = _field;
            cycle = _cycle;
            screen = nullptr;
            renderer = nullptr;
            window = nullptr;
        }

        ~engine()
        {
        }

        virtual int init(const char *title, const unsigned int width = 640, const unsigned int height = 480);
        virtual void start();
        virtual void cleanup();

        virtual void changeState(gameState::state *state);
        virtual void pushState(gameState::state *state);
        virtual void popState();

        virtual void events();
        virtual void update();
        virtual void draw();

        virtual void quit() { isRunning = false; }
    };

} // namespace gameEngine
