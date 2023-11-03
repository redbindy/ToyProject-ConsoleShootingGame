#include <Windows.h>

#include "MyDebug.h"
#include "GameManager.h"

int main()
{
	HANDLE primary = GetStdHandle(STD_OUTPUT_HANDLE);

#if _DEBUG
	if (primary == INVALID_HANDLE_VALUE)
	{
		return GetLastError();
	}
#endif /* _DEBUG */

	HANDLE secondary = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr,
		CONSOLE_TEXTMODE_BUFFER,
		nullptr
	);

#if _DEBUG
	if (secondary == INVALID_HANDLE_VALUE)
	{
		return GetLastError();
	}
#endif /* _DEBUG */

	ConsoleShootingGame::GameManager::CreateInstance(primary, secondary);
	{
		while (true)
		{
			ConsoleShootingGame::GameManager::GetInstance()->Run();
		}
	}
	ConsoleShootingGame::GameManager::DeleteInstance();

	return NO_ERROR;
}
