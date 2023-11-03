#include "GameManager.h"

namespace ConsoleShootingGame
{
	GameManager* GameManager::s_instance = nullptr;

	void GameManager::CreateInstance(const HANDLE primaryBuffer, const HANDLE secondaryBuffer)
	{
		ASSERT(primaryBuffer != nullptr && secondaryBuffer != nullptr, "HANDLE should be not null");

		if (s_instance != nullptr)
		{
			return;
		}

		s_instance = new GameManager(primaryBuffer, secondaryBuffer);
	}

	GameManager::GameManager(const HANDLE primaryBuffer, const HANDLE secondaryBuffer)
		: mPrimaryBuffer(primaryBuffer)
		, mSecondaryBuffer(secondaryBuffer)
		, mBackBuffer(mSecondaryBuffer)
		, mbSwitched(true)
		, mPlayerObject({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 })
	{
		for (int y = SCREEN_HEIGHT - 1; y >= 0; --y)
		{
			int x = SCREEN_WIDTH;

			mFrameBuffer[y * (SCREEN_WIDTH + 1) + x] = '\n';
			for (--x; x >= 0; --x)
			{
				mFrameBuffer[y * (SCREEN_WIDTH + 1) + x] = ' ';
			}
		}

		mFrameBuffer[BUFFER_SIZE - 1] = '\0';

		const COORD SIZE = {
			SCREEN_WIDTH + 2,
			SCREEN_HEIGHT
		};

		SetConsoleScreenBufferSize(mPrimaryBuffer, SIZE);
		SetConsoleScreenBufferSize(mSecondaryBuffer, SIZE);

		SMALL_RECT rect = {
			0,
			0,
			SCREEN_WIDTH,
			SCREEN_HEIGHT
		};

		int retValue = SetConsoleWindowInfo(mPrimaryBuffer, true, &rect);
		ASSERT(retValue != 0, "Failed SetConsoleWindowInfo");

		Sleep(100); // Sleep 없더라도 어떤 형태로든 딜레이를 줘야 다음 ASSERT 실패 안 함...

		retValue = SetConsoleWindowInfo(mSecondaryBuffer, true, &rect);
		ASSERT(retValue != 0, "Failed SetConsoleWindowInfo");
	}

	GameManager* GameManager::GetInstance()
	{
		ASSERT(s_instance != nullptr, "Should call CreateInstance before calling this function");

		return s_instance;
	}

	void GameManager::DeleteInstance()
	{
		delete s_instance;
	}

	void GameManager::Run()
	{
		mFrameBuffer[GetFrameIndex(mPlayerObject.mLocalOrigin.x, mPlayerObject.mLocalOrigin.y)] = ' ';

		mPlayerObject.Move();

		mFrameBuffer[GetFrameIndex(mPlayerObject.mLocalOrigin.x, mPlayerObject.mLocalOrigin.y)] = 'x';

		int retValue = WriteConsole(mBackBuffer, mFrameBuffer, BUFFER_SIZE, nullptr, nullptr);
		ASSERT(retValue != 0, "Failed WriteConsole");

		SetConsoleActiveScreenBuffer(mBackBuffer);

		if (mbSwitched)
		{
			mBackBuffer = mPrimaryBuffer;
		}
		else
		{
			mBackBuffer = mSecondaryBuffer;
		}

		mbSwitched = !mbSwitched;

		Sleep(1000 / FPS);
	}

	int GameManager::GetFrameIndex(const int x, const int y)
	{
		return mPlayerObject.mLocalOrigin.y * (SCREEN_WIDTH + 1) + mPlayerObject.mLocalOrigin.x;
	}
}
