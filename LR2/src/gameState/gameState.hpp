#pragma once

#include <memory>

namespace gameEngine
{
    class engine;
}

/**
 * @brief namespace for declaration class state
 * 
 */
namespace gameState
{
    /**
     * @brief declaration abstract class
     * 
     */
    class state
    {
    protected:
        SDL_Surface *bg;

    public:
        /**
         * @brief initialize state
         * 
         * @return int 
         */
        virtual int init() = 0;

        /**
         * @brief cleanup state
         * 
         */
        virtual void cleanup() = 0;

        /**
         * @brief pause state
         * 
         */
        virtual void pause() = 0;

        /**
         * @brief resume state
         * 
         */
        virtual void resume() = 0;

        /**
         * @brief receive events
         * 
         */
        virtual void events(gameEngine::engine *) = 0;

        /**
         * @brief update render
         * 
         */
        virtual void update(gameEngine::engine *) = 0;

        /**
         * @brief draw field
         * 
         */
        virtual void draw(gameEngine::engine *) = 0;

        /**
         * @brief Destroy the state object
         * 
         */
        virtual ~state() = default;
    };
} // namespace gameState
