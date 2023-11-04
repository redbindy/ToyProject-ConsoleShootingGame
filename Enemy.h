#pragma once

#include "eScreenInfo.h"
#include "MyDebug.h"
#include "GameObject.h"
#include "Ammo.h"
#include "IAttackable.h"

namespace ConsoleShootingGame
{
    enum
    {
        VECTOR_COUNT_ENEMY = 4
    };

    class Enemy : public GameObject, public IAttackable
    {
        friend class GameManager;

    public:
        Enemy(const Vector2D_t localOrigin);

        Ammo* AttackOrNull() override;
        void RetrieveAmmo(Ammo* ammo) override;

    private:
        Vector2D_t vectors[VECTOR_COUNT_ENEMY];

        Ammo* mAmmoOrNull;
    };
}