#pragma once

namespace ConsoleShootingGame
{
	enum eScreenInfo
	{
		SCREEN_WIDTH = 200,
		SCREEN_HEIGHT = 60,

		BUFFER_SIZE = SCREEN_HEIGHT * (SCREEN_WIDTH + 1) + 1,

		FPS = 60
	};
}