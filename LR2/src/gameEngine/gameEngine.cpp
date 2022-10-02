#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

#include "gameEngine.hpp"
#include "../gameState/gameState.hpp"
#include "../gameField/fieldAndCell.hpp"
#include "../gameCycle/mainCycle.hpp"
#include "../gameState/introState.hpp"

namespace gameEngine
{
    int engine::init(const char *title, const unsigned int width, const unsigned int height)
    {

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        window = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr)
        {
            std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        field = new gameField::field(16, 12);
        cycle = new gameCycle::mainCycle();

        isRunning = true;
        printf("gameEngine init\n");
        return 0;
    }

    void engine::cleanup()
    {
        while (!states.empty())
        {
            states.back()->cleanup();
            states.pop_back();
        }

        field->clear();
        delete field;
        delete cycle;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        printf("gameEngine cleanup\n");
    }

    void engine::changeState(gameState::state *state)
    {
        if (!states.empty())
        {
            states.back()->cleanup();
            states.pop_back();
        }

        states.push_back(state);
        states.back()->init();
    }

    void engine::pushState(gameState::state *state)
    {
        if (!states.empty())
            states.back()->pause();

        states.push_back(state);
        states.back()->init();
    }

    void engine::popState()
    {
        if (!states.empty())
        {
            states.back()->cleanup();
            states.pop_back();
        }

        if (!states.empty())
            states.back()->resume();
    }

    void engine::events()
    {
        states.back()->events(this);
    }

    void engine::update()
    {
        states.back()->update(this);
    }

    void engine::draw()
    {
        states.back()->draw(this);
    }

    void engine::start()
    {
        changeState(new introState());
        cycle = new gameCycle::mainCycle();

        while (isRunning)
        {
            events();
            update();
            draw();
        }
    }
} // namespace gameEngine
