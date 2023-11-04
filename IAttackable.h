#pragma once

#include "Ammo.h"

namespace ConsoleShootingGame
{
    class IAttackable
    {
    public:
        virtual Ammo* AttackOrNull() = 0;
        virtual void RetrieveAmmo(Ammo* ammo) = 0;

    private:
    };
}
