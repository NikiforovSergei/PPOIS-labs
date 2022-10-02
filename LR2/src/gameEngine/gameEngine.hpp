#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

//#include "../entityInterface/abstractEntity.cpp"
//#include "../gameField/fieldAndCell.cpp"
//#include "../gameCycle/mainCycle.cpp"
//#include "../gameState/gameState.hpp"
//#include "../gameState/autoState.cpp"
//#include "../gameState/introState.cpp"
//#include "../gameState/moderateState.cpp"

namespace gameState { class state; }
namespace gameField { class field; }
namespace gameCycle { class mainCycle; }


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
        engine();
        ~engine();

        int init(const char *title, const unsigned int width = 640, const unsigned int height = 480);
        void start();
        void cleanup();

        void changeState(gameState::state *state);
        void pushState(gameState::state *state);
        void popState();

        void events();
        void update();
        void draw();

        void quit() { isRunning = false; }
    };

    engine::engine(/* args */)
    {
        states = {};
        isRunning = false;
        field = nullptr;
        cycle = nullptr;
        screen = nullptr;
        renderer = nullptr;
        window = nullptr;
    }

    engine::~engine()
    {

    }
} // namespace gameEngine
