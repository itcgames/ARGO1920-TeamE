#ifndef TEXT
#define TEXT

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <iostream>
#include "Renderer.h"
class Text
{
public:

	Text(TTF_Font* font, std::string t_text, float xPos, float yPos );

	SDL_Rect* m_textRect;
	SDL_Texture* m_textTexture;
	SDL_Color White;
	TTF_Font* Font;

	void update(std::string t_newText);
	void render();
	void DestroyText();
};

#endif // !1