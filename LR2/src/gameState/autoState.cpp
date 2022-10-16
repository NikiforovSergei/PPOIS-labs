#include <iostream>
#include "autoState.hpp"
#include "../gameEngine/gameEngine.hpp"
#include "introState.hpp"
#include "moderateState.hpp"
#include "gameState.hpp"
#include "../gameCycle/mainCycle.hpp"
#include "../gameField/fieldAndCell.hpp"
#include <SDL2/SDL_image.h>

int autoState::init()
{
    bg = IMG_Load("../assets/cell.png");
    if (bg == nullptr)
    {
        std::cout << "IMG_Load Error: " << IMG_GetError() << std::endl;
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
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            game->quit();
            return;
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
                return;
            }
            break;
        }
    }
    SDL_Delay(1000);
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

    game->renderBG(autoTexture);

    game->renderField();

    SDL_DestroyTexture(autoTexture);
}

void autoState::draw(gameEngine::engine *game)
{
    SDL_RenderPresent(game->renderer);
}
