#pragma once

#include <Windows.h>

#include "Vector2D.h"
#include "eScreenInfo.h"

namespace ConsoleShootingGame
{
	class GameObject
	{
		friend class Player;

	public:
		GameObject() = delete;
		// GameObject(const Vector2D_t& other);
		// GameObject& operator=(const Vector2D_t& other);
		~GameObject() = default;

	protected:
		GameObject(const Vector2D_t localOrigin);

		Vector2D_t mLocalOrigin;
	};
}