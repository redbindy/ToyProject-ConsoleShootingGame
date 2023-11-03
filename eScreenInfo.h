#pragma once

namespace ConsoleShootingGame
{
	enum eScreenInfo
	{
		SCREEN_WIDTH = 40,
		SCREEN_HEIGHT = 30,

		BUFFER_SIZE = SCREEN_HEIGHT * (SCREEN_WIDTH + 1) + 1,

		FPS = 60
	};
}