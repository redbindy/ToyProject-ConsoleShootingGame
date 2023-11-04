#include "Player.h"

namespace ConsoleShootingGame
{
	Player::Player(const Vector2D_t localOrigin)
		: GameObject(localOrigin)
		, mVectors { { -1, 0 }, { 1, 0 }, { 0, 1 }, { -1, 1 }, { 1, 1 } }
	{

	}

	void Player::Move()
	{
		if (GetAsyncKeyState(VK_LEFT) && GameObject::mLocalOrigin.x > 0)
		{
			--mLocalOrigin.x;
		}

		if (GetAsyncKeyState(VK_RIGHT) && GameObject::mLocalOrigin.x < SCREEN_WIDTH - 1)
		{
			++mLocalOrigin.x;
		}

		if (GetAsyncKeyState(VK_UP) && GameObject::mLocalOrigin.y > 0)
		{
			--mLocalOrigin.y;
		}

		if (GetAsyncKeyState(VK_DOWN) && GameObject::mLocalOrigin.y < SCREEN_HEIGHT - 1)
		{
			++mLocalOrigin.y;
		}
	}

	void Player::Attack()
	{
		if (mAmmos.size() < AMMO_MAX)
		{
			GameObject* ammo = new GameObject(GameObject::mLocalOrigin);
		}
	}
}