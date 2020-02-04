#pragma once
#include<iostream>
#include "SDL.h"
#include "SDL_image.h"
class Renderer
{
public:
	static Renderer* Instance()
	{
		if (m_Instance == 0)
		{
			m_Instance = new Renderer();
			return m_Instance;
		}

		return m_Instance;
	}

	void setUpRenderer(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	SDL_Renderer* getRenderer();
	void renderToNull();

	SDL_Window* getWindow();
	void windowToNull();

	bool allOk();
private:	
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;

	static Renderer* m_Instance;
	bool isOk = false;
};
typedef Renderer Render;

