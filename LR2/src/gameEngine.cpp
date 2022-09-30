#pragma once

#include <stdio.h>
#include <iostream>
#include "gameEngine.hpp"

int gameEngine::engine::init(const char *title, const unsigned int width, const unsigned int height)
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

    isRunning = true;

    printf("gameEngine init\n");
}

void gameEngine::engine::cleanup()
{

    while (!states.empty())
    {
        states.back()->cleanup();
        states.pop_back();
    }

    printf("gameEngine cleanup\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void gameEngine::engine::changeState(gameState::state *state)
{
    if (!states.empty())
    {
        states.back()->cleanup();
        states.pop_back();
    }

    states.push_back(state);
    states.back()->init();
}

void gameEngine::engine::pushState(gameState::state *state)
{
    if (!states.empty())
        states.back()->pause();

    states.push_back(state);
    states.back()->init();
}

void gameEngine::engine::popState()
{
    if (!states.empty())
    {
        states.back()->cleanup();
        states.pop_back();
    }

    if (!states.empty())
        states.back()->resume();
}

void gameEngine::engine::events()
{
    states.back()->events(this);
}

void gameEngine::engine::update()
{
    states.back()->update(this);
}

void gameEngine::engine::draw()
{
    states.back()->draw(this);
}
