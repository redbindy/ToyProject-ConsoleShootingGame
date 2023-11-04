#include "Player.h"

namespace ConsoleShootingGame
{
	clock_t Player::s_lastPressTime = clock();

	Player::Player(const Vector2D_t localOrigin)
		: GameObject(localOrigin)
		, mVectors { { -1, 0 }, { 1, 0 }, { 0, 1 }, { -1, 1 }, { 1, 1 } }
	{
		for (int i = AMMO_MAX - 1; i >= 0; --i)
		{
			mAmmos.push(new Ammo({ 0, 0 }, -1));
		}
	}

	Player::~Player()
	{
		while (!mAmmos.empty())
		{
			delete mAmmos.front();
			mAmmos.pop();
		}
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

	Ammo* Player::AttackOrNull()
	{
		if (mAmmos.empty() || !GetAsyncKeyState(VK_SPACE) || clock() - s_lastPressTime < ATTACK_DELAY)
		{
			return nullptr;
		}

		Ammo* ammo = mAmmos.front();
		{
			ammo->mLocalOrigin.x = GameObject::mLocalOrigin.x;
			ammo->mLocalOrigin.y = GameObject::mLocalOrigin.y;
		}
		mAmmos.pop();

		s_lastPressTime = clock();

		return ammo;
	}

	void Player::RetrieveAmmo(Ammo* ammo)
	{
		ASSERT(ammo != nullptr, "ammo should be not null");

		mAmmos.push(ammo);
	}
}