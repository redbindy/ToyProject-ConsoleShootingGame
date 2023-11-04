#pragma once

#include <Windows.h>
#include <queue>
#include <random>

#include "eScreenInfo.h"
#include "Player.h"
#include "Ammo.h"
#include "Enemy.h"

namespace ConsoleShootingGame
{
	class Player;

	class GameManager final
	{
	public:
		static void CreateInstance(const HANDLE primaryBuffer, const HANDLE secondaryBuffer);
		static GameManager* GetInstance();
		static void DeleteInstance();

		GameManager() = delete;
		GameManager(const GameManager& other) = delete;
		GameManager* operator=(const GameManager& other) = delete;
		~GameManager();

		void Run();
		void RegisterAmmo(Ammo* ammo);

	private:
		GameManager(const HANDLE primaryBuffer, const HANDLE secondaryBuffer);

		int GetFrameIndex(const int x, const int y);
		void overwriteObject(const wchar_t objectPixel);

		static GameManager* s_instance;

		HANDLE mPrimaryBuffer;
		HANDLE mSecondaryBuffer;
		HANDLE mBackBuffer;

		bool mbSwitched;

		wchar_t mFrameBuffer[BUFFER_SIZE];

		Player mPlayerObject;
		std::queue<Ammo*> mPlayerAmmos;

		std::vector<Enemy> mEnemies;
	};
}
