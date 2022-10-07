#include <iostream>
#include "autoState.hpp"
#include "../gameEngine/gameEngine.hpp"
#include "introState.hpp"
#include "moderateState.hpp"
#include "gameState.hpp"
#include "../gameCycle/mainCycle.hpp"

int autoState::init()
{
    bg = SDL_LoadBMP("../assets/autoStateBG.bmp");
    if (bg == nullptr)
    {
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    return 0;
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
                game->changeState(new introState());
                break;
            case SDLK_2:
                game->changeState(new moderateState());
                break;
            case SDLK_ESCAPE:
                game->quit();
                break;
            }
            break;
        }
    }

    game->cycle->nextStep(game->field);
}

void autoState::update(gameEngine::engine *game)
{
    SDL_Texture *autoTexture = SDL_CreateTextureFromSurface(game->renderer, bg);
    if (autoTexture == nullptr)
    {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_RenderClear(game->renderer);
    SDL_RenderCopy(game->renderer, autoTexture, NULL, NULL);
    SDL_DestroyTexture(autoTexture);
}

void autoState::draw(gameEngine::engine *game)
{
    SDL_RenderPresent(game->renderer);
}
