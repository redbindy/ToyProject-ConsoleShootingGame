#pragma once

#include <Windows.h>

#include "Vector2D.h"
#include "eScreenInfo.h"

namespace ConsoleShootingGame
{
	class GameObject
	{
		friend class GameManager;

	public:
		GameObject(const Vector2D_t localOrigin);
		// GameObject(const Vector2D_t& other);
		// GameObject& operator=(const Vector2D_t& other);
		~GameObject() = default;

		virtual void Attack();

	protected:
		Vector2D_t mLocalOrigin;
	};
}