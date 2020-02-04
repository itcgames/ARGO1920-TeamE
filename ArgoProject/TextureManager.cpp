#include "TextureManager.h"

TextureManager* TextureManager::m_Instance = 0;


TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

bool TextureManager::Load(std::string fileName, std::string id)
{
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
	if (tempSurface == 0)
	{
		std::cout << "ERROR";
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), tempSurface);

	SDL_FreeSurface(tempSurface);

	// if it goes in here we G
	if (texture != 0)
	{
		m_textureMap[id] = texture;
		return true;
	}

	//Last check if it reaches here something went badly wrong
	std::cout << "ERROR";
	return false;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect startRect;
	SDL_Rect destRect;

	startRect.x = 0;
	startRect.y = 0;

	startRect.w = destRect.w = width;
	startRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(Render::Instance()->getRenderer(), m_textureMap[id], &startRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);

	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(Render::Instance()->getRenderer(), m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

SDL_Texture* TextureManager::getTexture(std::string id)
{
	return m_textureMap[id];
}
