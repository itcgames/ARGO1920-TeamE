#pragma once
#include<iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <map>
#include "Renderer.h"


class TextureManager
{
public:
	static TextureManager* Instance()
	{
		if (m_Instance == 0)
		{
			m_Instance = new TextureManager();
			return m_Instance;
		}

		return m_Instance;
	}

	bool Load(std::string fileName, std::string id);

	// Used to draw Static Image
	void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Used to draw animated sprites
	void DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_RendererFlip flip = SDL_FLIP_NONE);

	SDL_Texture* getTexture(std::string id);

	std::map<std::string, SDL_Texture*> getTextureMap() { return m_textureMap; }

private:
	TextureManager();
	~TextureManager();


	std::map<std::string, SDL_Texture*> m_textureMap;

	static TextureManager* m_Instance;

};

typedef TextureManager MyTextureManager;

