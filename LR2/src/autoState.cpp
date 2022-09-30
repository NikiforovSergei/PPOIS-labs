#pragma once

#include "gameEngine.hpp"
#include "autoState.hpp"
#include <SDL2/SDL_video.h>

#include "moderateState.hpp"
#include "introState.hpp"

int autoState::init()
{
    bg = SDL_LoadBMP("../assets/autoStateBG.bmp");
}

void autoState::cleanup()
{
    SDL_FreeSurface(bg);

    printf("autoState cleanup\n");
}

void autoState::pause()
{
    printf("autoState pause\n");
}

void autoState::resume()
{
    printf("autoState resume\n");
}

void autoState::events(gameEngine::engine *game)
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
            case SDLK_0:
                game->changeState(introState::instance());
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

void autoState::update(gameEngine::engine *game)
{
    SDL_Texture *autoTexture = SDL_CreateTextureFromSurface(game->renderer, bg);
    SDL_RenderClear(game->renderer);
}

void draw(gameEngine::engine *game)
{
    SDL_RenderPresent(game->renderer);
}
