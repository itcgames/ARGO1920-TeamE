#include "Renderer.h"

Renderer* Renderer::m_Instance = 0;

void Renderer::setUpRenderer(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}

		isOk = true;

	}
	else
	{
		isOk = false;
	}
}

SDL_Renderer* Renderer::getRenderer()
{
	return renderer;
}

void Renderer::renderToNull()
{
	renderer = NULL;
}

SDL_Window* Renderer::getWindow()
{
	return window;
}

void Renderer::windowToNull()
{
	window = NULL;
}

bool Renderer::allOk()
{
	return isOk;
}
