#pragma once

#include <Windows.h>

#include "MyDebug.h"
#include "eScreenInfo.h"
#include "Player.h"

namespace ConsoleShootingGame
{
	class GameManager final
	{
	public:
		static void CreateInstance(const HANDLE primaryBuffer, const HANDLE secondaryBuffer);
		static GameManager* GetInstance();
		static void DeleteInstance();

		GameManager() = delete;
		GameManager(const GameManager& other) = delete;
		GameManager* operator=(const GameManager& other) = delete;

		void Run();

	private:
		GameManager(const HANDLE primaryBuffer, const HANDLE secondaryBuffer);

		int GetFrameIndex(const int x, const int y);
		void overwriteObject(const wchar_t pixel);

		static GameManager* s_instance;

		HANDLE mPrimaryBuffer;
		HANDLE mSecondaryBuffer;
		HANDLE mBackBuffer;

		bool mbSwitched;

		wchar_t mFrameBuffer[BUFFER_SIZE];

		Player mPlayerObject;
	};
}
