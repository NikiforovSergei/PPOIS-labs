#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "gameEngine.hpp"
#include "../gameState/gameState.hpp"
#include "../gameField/fieldAndCell.hpp"

namespace gameEngine
{
    int engine::init(const char *title, const uint width,
                     const uint height)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            std::cout << "IMG_Init error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }

        window = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

        screen = SDL_GetWindowSurface(window);

        isRunning = true;
        printf("gameEngine init\n");
        return 0;
    }

    void engine::renderBG(SDL_Texture *tex)
    {
        const int widthField = field->size().first;
        const int heightField = field->size().second;
        int widthWin;
        int heightWin;
        SDL_GetWindowSize(window, &widthWin, &heightWin);
        SDL_Rect cellBlock;
        cellBlock.w = widthWin / widthField;
        cellBlock.h = heightWin / heightField;

        for (int i = 0; i < heightField; ++i)
            for (int j = 0; j < widthField; ++j)
            {
                cellBlock.x = j * cellBlock.w;
                cellBlock.y = i * cellBlock.h;
                SDL_RenderCopy(renderer, tex, NULL, &cellBlock);
            }
    }

    void engine::renderField()
    {
        auto widthField = field->size().first;
        auto heightField = field->size().second;
        auto widthWin = 0;
        auto heightWin = 0;
        SDL_GetWindowSize(window, &widthWin, &heightWin);
        auto widthCell = widthWin / widthField;
        auto heightCell = heightWin / heightField;

        for (int i = 0; i < widthField; ++i)
            for (int j = 0; j < heightField; ++j)
            {
                gameField::cell *tmpCell = field->getCell(i, j);
                int pos = 0;
                for (animal *k : tmpCell->get<animal>())
                {
                    SDL_Texture *entityTex = IMG_LoadTexture(renderer, k->getSpritePath().c_str());
                    pos = renderEntity(widthCell, heightCell, i, j, entityTex, pos);
                }

                for (animal *k : tmpCell->get<grassEater>())
                {
                    SDL_Texture *entityTex = IMG_LoadTexture(renderer, k->getSpritePath().c_str());
                    pos = renderEntity(widthCell, heightCell, i, j, entityTex, pos);
                }

                if (tmpCell->get<plant>() != nullptr)
                {
                    SDL_Texture *entityTex = IMG_LoadTexture(renderer, tmpCell->get<plant>()->getSpritePath().c_str());
                    pos = renderEntity(widthCell, heightCell, i, j, entityTex, pos);
                }
            }
    }

    const int engine::renderEntity(const int widthCell, const int heightCell,
                                   const int cellX, const int cellY,
                                   SDL_Texture *entityTexture, const int pos)
    {
        SDL_Rect entityRect;
        entityRect.w = widthCell / 2;
        entityRect.h = heightCell / 2;
        entityRect.x = widthCell * cellX + (widthCell / 2) * (pos % 2);
        entityRect.y = heightCell * cellY + (heightCell / 2) * (floor(pos / 2));
        SDL_RenderCopy(renderer, entityTexture, nullptr, &entityRect);
        return pos + 1;
    }

    void engine::cleanup()
    {
        while (!states.empty())
        {
            delete states.back();
            states.pop_back();
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        printf("gameEngine cleanup\n");
    }

    void engine::changeState(gameState::state *state)
    {
        if (!states.empty())
        {
            delete states.back();
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

            delete states.back();
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
        while (isRunning)
        {
            events();
            update();
            draw();
        }
    }
} // namespace gameEngine
