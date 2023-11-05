#pragma once

namespace ConsoleShootingGame
{
    class ICollisionListener
    {
    public:
        virtual void OnCollision() = 0;

    private:
    };
}
