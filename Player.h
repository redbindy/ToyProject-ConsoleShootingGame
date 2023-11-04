#pragma once

#include "GameObject.h"
#include <queue>

namespace ConsoleShootingGame
{
	enum
	{
		VECTOR_COUNT = 5,

		AMMO_MAX = 4
	};

	class Player final : public GameObject
	{
		friend class GameManager;

	public:
		Player(const Vector2D_t localOrigin);
		Player(const Player& other) = delete;
		Player& operator=(const Player& other) = delete;

		void Move();
		void Attack();

	private:
		Vector2D_t mVectors[VECTOR_COUNT];

		std::queue<GameObject*> mAmmos;
	};
}