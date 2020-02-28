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
#include "LevelLoader.h"

using namespace std;

#define DEBUG_MSG

using namespace std;
int main(int argc, char* argv[])
{
	DEBUG_MSG("Game Object Created");
	GameData data;
	LevelLoader::load(".\\ASSETS\\YAML\\Level1.yaml", data);
	Game* game = new Game(data);
	//FrameRate Capping 
	const int Fps = 60;
	const int frameDelay = 1000 / Fps;

	Uint32 framestart;

	int frameTime;

	SDL_DisplayMode DM;
   SDL_GetDesktopDisplayMode(0, &DM);
   auto Width = DM.w;
   auto Height = DM.h;

	game->init("Argo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 3840, 2160, true);//2500, 2000, false);

	while (game->running() == true){
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