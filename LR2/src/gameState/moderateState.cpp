#include <iostream>
#include "moderateState.hpp"
#include "../gameEngine/gameEngine.hpp"
#include "autoState.hpp"
#include "introState.hpp"
#include "gameState.hpp"
#include "../gameCycle/mainCycle.hpp"

int moderateState::init()
{
    bg = SDL_LoadBMP("../assets/moderateStateBG.bmp");
    if (bg == nullptr)
    {
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    return 0;
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
                game->changeState(new introState());
                break;
            case SDLK_1:
                game->changeState(new autoState());
                break;
            case SDLK_n:
                game->cycle->nextStep(game->field);
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
    if (moderateTexture == nullptr)
    {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_RenderClear(game->renderer);
    SDL_RenderCopy(game->renderer, moderateTexture, NULL, NULL);
    SDL_DestroyTexture(moderateTexture);
}

void moderateState::draw(gameEngine::engine *game)
{
    SDL_RenderPresent(game->renderer);
}