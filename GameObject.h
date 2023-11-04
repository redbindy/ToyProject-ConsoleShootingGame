#pragma once

#include "Vector2D.h"

namespace ConsoleShootingGame
{
	class GameObject
	{
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