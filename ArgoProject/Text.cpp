#include "Text.h"

Text::Text(TTF_Font* font, std::string t_text,  float xPos, float yPos)
{
	White = { 255,255,255 };

	m_textRect = new SDL_Rect();

	Font = font;

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, t_text.c_str(), White);
	m_textTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surfaceMessage);

	m_textRect->x = xPos;
	m_textRect->y = yPos;

	TTF_SizeText(Font, t_text.c_str(), &m_textRect->w, &m_textRect->h);
}

void Text::render()
{
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_textTexture, NULL, m_textRect);
}