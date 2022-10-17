#include <iostream>
#include "moderateState.hpp"
#include "../gameEngine/gameEngine.hpp"
#include "autoState.hpp"
#include "introState.hpp"
#include "gameState.hpp"
#include "../gameCycle/mainCycle.hpp"
#include <SDL2/SDL_image.h>

int moderateState::init()
{
    bg = IMG_Load("../assets/cell.png");
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
            case SDLK_1:
                game->changeState(new autoState());
                break;
            case SDLK_n:
                game->cycle->nextStep(game->field);
                break;
            case SDLK_ESCAPE:
                game->quit();
                return;
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

    game->renderBG(moderateTexture);

    game->renderField();

    SDL_DestroyTexture(moderateTexture);
}

void moderateState::draw(gameEngine::engine *game)
{
    SDL_RenderPresent(game->renderer);
}