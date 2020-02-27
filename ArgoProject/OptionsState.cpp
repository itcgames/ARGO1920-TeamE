#include "OptionsState.h"

const std::string OptionsState::m_optionsID = "OPTIONS";

OptionsState::OptionsState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
}

void OptionsState::update()
{

}
void OptionsState::render()
{
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_exitButtonTexture, NULL, m_exitButton);
}
void OptionsState::processEvents(bool& isRunning)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.x > m_exitButton->x && event.button.x < m_exitButton->x + m_exitButton->w
				&&
				event.button.y > m_exitButton->y && event.button.y < m_exitButton->y + m_exitButton->h)
			{
				m_stateMachine->changeState(new MenuState(m_cameraDimensions,m_stateMachine));
			}
			break;
		default:
			break;
		}
	}
}

bool OptionsState::onEnter()
{
	m_exitButton = new SDL_Rect();
	m_exitButton->x = m_cameraDimensions.x * 0.2;
	m_exitButton->y = m_cameraDimensions.y * 0.8;
	m_exitButton->w = m_cameraDimensions.x * 0.6;
	m_exitButton->h = m_cameraDimensions.y * 0.2;

	SDL_Surface* m_exitButtonSurface = IMG_Load("Assets/Button.png");
	m_exitButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_exitButtonSurface);
	SDL_FreeSurface(m_exitButtonSurface);
	return true;
}
bool OptionsState::onExit()
{
	m_exitButton = nullptr;
	m_exitButtonTexture = nullptr;
	return true;
}