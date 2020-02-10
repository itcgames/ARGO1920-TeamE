#pragma once
#include "SDL_net.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Server
{
public:
	void init();
	void cleanUp();
private:
	IPaddress ip;
	TCPsocket server;
	TCPsocket client;
};

