#pragma once

#include <time.h>

#include "eScreenInfo.h"
#include "MyDebug.h"
#include "GameObject.h"
#include "Ammo.h"
#include "IAttackable.h"
#include "ICollisionListener.h"

namespace ConsoleShootingGame
{
    enum
    {
        VECTOR_COUNT_ENEMY = 4,

        ATTACK_DELAY_ENEMY = 1000
    };

    class Enemy : public GameObject, public IAttackable, public ICollisionListener
    {
        friend class GameManager;

    public:
        Enemy(const Vector2D_t localOrigin);

        Ammo* AttackOrNull() override;

        void Reload();

        void OnCollision();

    private:
        bool mIsAlive;

        Vector2D_t mVectors[VECTOR_COUNT_ENEMY];

        Ammo* mAmmo;

        static clock_t s_lastAttackTime;
    };
}