#pragma once

#include <Windows.h>
#include <queue>
#include <time.h>

#include "eScreenInfo.h"
#include "Player.h"
#include "Ammo.h"
#include "Enemy.h"

namespace ConsoleShootingGame
{
	enum
	{
		ENEMY_COUNT = 10
	};

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

		bool Run();
		void RegisterAmmo(Ammo* ammo);

	private:
		GameManager(const HANDLE primaryBuffer, const HANDLE secondaryBuffer);

		int GetFrameIndex(const int x, const int y);
		void overwriteObject(const wchar_t playerPixel, const wchar_t enemyPixel);

		static GameManager* s_instance;

		HANDLE mPrimaryBuffer;
		HANDLE mSecondaryBuffer;
		HANDLE mBackBuffer;

		bool mbSwitched;

		wchar_t mFrameBuffer[BUFFER_SIZE];

		Player mPlayerObject;
		std::queue<Ammo*> mPlayerAmmos;

		std::queue<Enemy*> mEnemyQueue;
		std::vector<Enemy*> mEnemies;

		inline bool isClipPixel(const int x, const int y)
		{
			return x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT;
		}
	};
}
