#pragma once

#include "gameEngine.hpp"
#include "moderateState.hpp"
#include <SDL2/SDL_video.h>

#include "autoState.hpp"
#include "introState.hpp"

int moderateState::init()
{
    bg = SDL_LoadBMP("../assets/moderateStateBG.bmp");
}

void moderateState::cleanup()
{
    SDL_FreeSurface(bg);

    printf("moderateState cleanup\n");
}

void moderateState::pause()
{
    printf("moderateState pause\n");
}

void moderateState::resume()
{
    printf("moderateState resume\n");
}

void moderateState::events(gameEngine::engine *game)
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
            case SDLK_1:
                game->changeState(autoState::instance());
                break;
            case SDLK_ESCAPE:
                game->quit();
                break;
            }
            break;
        }
    }
}

void moderateState::update(gameEngine::engine *game)
{
    SDL_Texture *moderateTexture = SDL_CreateTextureFromSurface(game->renderer, bg);
    SDL_RenderClear(game->renderer);
}

void draw(gameEngine::engine *game)
{
    SDL_RenderPresent(game->renderer);
}
