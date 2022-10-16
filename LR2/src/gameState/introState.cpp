#include "introState.hpp"
#include <iostream>
#include "../gameEngine/gameEngine.hpp"
#include "autoState.hpp"
#include "moderateState.hpp"
#include "gameState.hpp"

int introState::init()
{
    bg = SDL_LoadBMP("../assets/introStateBG.bmp");
    if (bg == nullptr)
    {
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    return 0;
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
            return;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_1:
                game->changeState(new autoState());
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
}

void introState::update(gameEngine::engine *game)
{
    SDL_Texture *introTexture = SDL_CreateTextureFromSurface(game->renderer, bg);
    if (introTexture == nullptr)
    {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_RenderClear(game->renderer);
    SDL_RenderCopy(game->renderer, introTexture, NULL, NULL);
    SDL_DestroyTexture(introTexture);
}

void introState::draw(gameEngine::engine *game)
{
    SDL_RenderPresent(game->renderer);
}
