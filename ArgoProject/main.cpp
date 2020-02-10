#ifdef _DEBUG 
#pragma comment(lib,"libyaml-cppmdd.lib")
#else 
#pragma comment(lib,"libyaml-cppmd.lib")


#endif 

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#include "yaml-cpp\yaml.h"

#include "Game.h"

using namespace std;

#define DEBUG_MSG

using namespace std;
int main(int argc, char* argv[])
{
	DEBUG_MSG("Game Object Created");
	Game* game = new Game();

	//FrameRate Capping 
	const int Fps = 60;
	const int frameDelay = 1000 / Fps;

	Uint32 framestart;
	int frameTime;

	game->init("Argo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2500, 2000, false);


	while (game->running() == true)
	{
		framestart = SDL_GetTicks();

		game->processEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - framestart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}


	game->cleanUp();
	return 0;
}