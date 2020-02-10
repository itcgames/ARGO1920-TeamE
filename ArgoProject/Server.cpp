#include "Server.h"

void Server::init()
{

	if (SDLNet_Init() < 0) 
	{ 
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError()); 
		exit(EXIT_FAILURE); 
	}

	server = SDLNet_TCP_Open(&ip);

	if (SDLNet_ResolveHost(&ip, "149.153.106.174", 2000) < 0)
	{ 
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE); 
	}

	if (!(server = SDLNet_TCP_Open(&ip))) 
	{ 
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError()); 
		exit(EXIT_FAILURE); 
	}
}

void Server::cleanUp()
{
	SDLNet_Quit();
}
