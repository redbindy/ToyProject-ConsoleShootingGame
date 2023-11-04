#include "Enemy.h"

namespace ConsoleShootingGame
{
    Enemy::Enemy(const Vector2D_t localOrigin)
        : GameObject(localOrigin)
        , vectors{ {-2, 0}, {-1, 0}, {1, 0}, {2,0} }
        , mAmmoOrNull(new Ammo({ 0, 0 }, 1))
    {

    }

    Ammo* Enemy::AttackOrNull()
    {
        if (mAmmoOrNull->mLocalOrigin.y == SCREEN_HEIGHT)
        {
            return nullptr;
        }

        return mAmmoOrNull;
    }

    void Enemy::RetrieveAmmo(Ammo* ammo)
    {
        mAmmoOrNull->mLocalOrigin = GameObject::mLocalOrigin;
    }
}