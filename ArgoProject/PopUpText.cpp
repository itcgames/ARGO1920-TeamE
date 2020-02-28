#include "PopUpText.h"

PopUpText::PopUpText(TTF_Font* font, std::string t_text, float xPos, float yPos, int t_timeAlive) :
	m_font(font), popUpText(t_text), m_pos(Vector2(xPos, yPos)), timeAlive(t_timeAlive)
{
	m_text = new Text(m_font, popUpText, m_pos.x, m_pos.y);
}

PopUpText::~PopUpText()
{
}

void PopUpText::update()
{
	if (timeAlive < 0)
	{
		m_text = nullptr;
		delete m_text;
	}
	else
	{
		timeAlive--;
	}
}

void PopUpText::render()
{
	if (m_text != nullptr)
	{
		m_text->render();
	}
}
