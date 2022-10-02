#pragma once

namespace gameEngine { class engine; }

namespace gameState
{
    class state
    {
    public:
        virtual int init() = 0;
        virtual void cleanup() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void events(gameEngine::engine*) = 0;
        virtual void update(gameEngine::engine*) = 0;
        virtual void draw(gameEngine::engine*) = 0;

        virtual ~state() = 0;
    };
} // namespace gameState
