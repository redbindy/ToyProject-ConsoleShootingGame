#pragma once

#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <queue>
#include <time.h>
#include <mmsystem.h>

#include "eScreenInfo.h"
#include "GameObject.h"
#include "Ammo.h"
#include "IMovable.h"
#include "IAttackable.h"
#include "ICollisionListener.h"

namespace ConsoleShootingGame
{
	enum
	{
		VECTOR_COUNT_PLAYER = 5,

		MAX_HP = 5,
		AMMO_MAX = 4,

		ATTACK_DELAY_PLAYER = 250
	};

	class Player final : public GameObject, public IMovable, public IAttackable, public ICollisionListener
	{
		friend class GameManager;

	public:
		Player(const Vector2D_t localOrigin);
		Player(const Player& other) = delete;
		Player& operator=(const Player& other) = delete;
		~Player();

		void Move() override;
		Ammo* AttackOrNull() override;

		void RetrieveAmmo(Ammo* ammo);

		void OnCollision() override;

	private:
		int mHp;

		Vector2D_t mVectors[VECTOR_COUNT_PLAYER];

		std::queue<Ammo*> mAmmos;

		static clock_t s_lastPressTime;
	};
}