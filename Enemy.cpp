#include "Enemy.h"

namespace ConsoleShootingGame
{
    clock_t Enemy::s_lastAttackTime = clock();

    Enemy::Enemy(const Vector2D_t localOrigin)
        : GameObject(localOrigin)
        , mIsAlive(true)
        , mVectors{ {-2, 0}, {-1, 0}, {1, 0}, {2,0} }
        , mAmmo(new Ammo(localOrigin, 1))
    {

    }

    Ammo* Enemy::AttackOrNull()
    {
        if (mAmmo->mLocalOrigin.y == SCREEN_HEIGHT || clock() - s_lastAttackTime < ATTACK_DELAY_ENEMY)
        {
            return nullptr;
        }

        return mAmmo;
    }

    void Enemy::Reload()
    {
        mAmmo->mLocalOrigin = GameObject::mLocalOrigin;
    }

    void Enemy::OnCollision()
    {
        mIsAlive = false;
    }
}