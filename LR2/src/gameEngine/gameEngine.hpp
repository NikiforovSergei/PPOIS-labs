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

/**
 * @brief namespace for deaclaration class engine
 * 
 */
namespace gameEngine
{
    /**
     * @brief declaration class engine
     * 
     */
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

        /**
         * @brief Construct a new engine object
         * 
         * @param _field 
         * @param _cycle 
         */
        engine(gameField::field *_field, gameCycle::mainCycle *_cycle)
            : field(_field), cycle(_cycle), isRunning(false), screen(nullptr), renderer(nullptr), window(nullptr)
        {
        }

        /**
         * @brief Destroy the engine object
         * 
         */
        ~engine()
        {
        }

        /**
         * @brief render field
         * 
         */
        void renderField();
        
        /**
         * @brief render background of field
         * 
         * @param tex 
         */
        void renderBG(SDL_Texture *tex);

        /**
         * @brief init engine
         * 
         * @param title of window
         * @param width of window
         * @param height of window
         * @return int 
         */
        virtual int init(const char *title, const uint width = 640u, const uint height = 480u);

        /**
         * @brief start game(game cycle)
         * 
         */
        virtual void start();

        /**
         * @brief cleanup all states in engine
         * 
         */
        virtual void cleanup();

        /**
         * @brief change state
         * 
         * @param state 
         */
        virtual void changeState(gameState::state *state);

        /**
         * @brief push state
         * 
         * @param state 
         */
        virtual void pushState(gameState::state *state);

        /**
         * @brief pop state
         * 
         */
        virtual void popState();

        /**
         * @brief receive events
         * 
         */
        virtual void events();

        /**
         * @brief update render
         * 
         */
        virtual void update();

        /**
         * @brief draw field
         * 
         */
        virtual void draw();

        /**
         * @brief quit game
         * 
         */
        virtual void quit() { isRunning = false; }

    private:
        /**
         * @brief render entity
         * 
         * @param widthCell 
         * @param heightCell 
         * @param cellX 
         * @param cellY 
         * @param entityTexture 
         * @param pos 
         * @param maxEntityCount 
         * @return const int 
         */
        const int renderEntity(const int widthCell, const int heightCell,
                               const int cellX, const int cellY,
                               SDL_Texture* entityTexture, const int pos, const int maxEntityCount);
    };

} // namespace gameEngine
