#ifndef POPUPTEXT
#define POPUPTEXT

#include "Text.h";
#include "Vector2.h"

class PopUpText
{
public:
	PopUpText(TTF_Font* font, std::string t_text, float xPos, float yPos,int t_timeAlive);
	~PopUpText();

	void update();
	void render();

	TTF_Font* m_font;
	std::string popUpText;
	Vector2 m_pos;

	Text *m_text;

	int timeAlive = 60;
};

#endif

