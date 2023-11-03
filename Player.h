#pragma once

#include "GameObject.h"

namespace ConsoleShootingGame
{
	class Player final : GameObject
	{
	public:
		Player();
		Player(const Player& other) = delete;
		Player& operator=(const Player& other) = delete;

		void Move();
		void Attack() override;

	private:
	};
}