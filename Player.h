#pragma once

#include <Windows.h>
#include <queue>
#include <time.h>

#include "eScreenInfo.h"
#include "GameObject.h"
#include "Ammo.h"
#include "IMovable.h"
#include "IAttackable.h"

namespace ConsoleShootingGame
{
	enum
	{
		VECTOR_COUNT_PLAYER = 5,

		AMMO_MAX = 4,

		ATTACK_DELAY = 500
	};

	class Player final : public GameObject, public IMovable, public IAttackable
	{
		friend class GameManager;

	public:
		Player(const Vector2D_t localOrigin);
		Player(const Player& other) = delete;
		Player& operator=(const Player& other) = delete;
		~Player();

		void Move() override;
		Ammo* AttackOrNull() override;

		void RetrieveAmmo(Ammo* ammo) override;

	private:
		Vector2D_t mVectors[VECTOR_COUNT_PLAYER];

		std::queue<Ammo*> mAmmos;

		static clock_t s_lastPressTime;
	};
}