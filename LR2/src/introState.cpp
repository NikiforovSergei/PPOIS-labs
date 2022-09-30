#pragma once

#include "gameEngine.hpp"
#include "introState.hpp"
#include <SDL2/SDL_video.h>

#include "moderateState.hpp"
#include "autoState.hpp"

int introState::init()
{
    bg = SDL_LoadBMP("../assets/introStateBG.bmp");
}

void introState::cleanup()
{
    SDL_FreeSurface(bg);

    printf("introState cleanup\n");
}

void introState::pause()
{
    printf("introState pause\n");
}

void introState::resume()
{
    printf("introState resume\n");
}

void introState::events(gameEngine::engine *game)
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            game->quit();
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_1:
                game->changeState(autoState::instance());
                break;
            case SDLK_2:
                game->changeState(moderateState::instance());
                break;
            case SDLK_ESCAPE:
                game->quit();
                break;
            }
            break;
        }
    }
}

void introState::update(gameEngine::engine *game)
{
    SDL_Texture *introTexture = SDL_CreateTextureFromSurface(game->renderer, bg);
    SDL_RenderClear(game->renderer);
}

void draw(gameEngine::engine *game)
{
    SDL_RenderPresent(game->renderer);
}
