#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <memory>

namespace gameState
{
    class state;
}
namespace gameField
{
    class field;
}
namespace gameCycle
{
    class mainCycle;
}

namespace gameEngine
{
    class engine
    {
    private:
        std::vector<gameState::state *> states;
        bool isRunning;

    public:
        gameField::field *field;
        gameCycle::mainCycle *cycle;
        SDL_Surface *screen;
        SDL_Renderer *renderer;
        SDL_Window *window;

        engine(gameField::field *_field, gameCycle::mainCycle *_cycle)
            : field(_field), cycle(_cycle), isRunning(false), screen(nullptr), renderer(nullptr), window(nullptr)
        {
        }

        ~engine()
        {
        }

        void renderField();
        void renderBG(SDL_Texture *tex);

        virtual int init(const char *title, const uint width = 640u, const uint height = 480u);
        virtual void start();
        virtual void cleanup();

        virtual void changeState(gameState::state *state);
        virtual void pushState(gameState::state *state);
        virtual void popState();

        virtual void events();
        virtual void update();
        virtual void draw();

        virtual void quit() { isRunning = false; }

    private:
        const int renderEntity(const int widthCell, const int heightCell,
                               const int cellX, const int cellY,
                               SDL_Texture* entityTexture, const int pos);
    };

} // namespace gameEngine
