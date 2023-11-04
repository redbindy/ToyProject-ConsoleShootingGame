#pragma once

#include "MyDebug.h"
#include "GameObject.h"
#include "IMovable.h"

namespace ConsoleShootingGame
{
    class Ammo : public GameObject, public IMovable
    {
        friend class Player;
        friend class Enemy;
        friend class GameManager;

    public:
        void Move() override;

    private:
        Ammo(const Vector2D_t localOrigin, const int direction);

        const int mDirection;
    };
}