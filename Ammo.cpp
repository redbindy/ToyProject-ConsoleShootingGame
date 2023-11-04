#include "Ammo.h"

namespace ConsoleShootingGame
{
    Ammo::Ammo(const Vector2D_t localOrigin, const int direction)
        : GameObject(localOrigin)
        , mDirection(direction)
    {
        ASSERT((direction == 1 || direction == -1), "direction should be 1 or -1");
    }

    void Ammo::Move()
    {
        GameObject::mLocalOrigin.y += mDirection;
    }
}