#include "EndState.h"

const std::string EndState::m_endID = "END";

EndState::EndState(Vector2& t_screenDimensions,GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
}

void EndState::update()
{

}
void EndState::render()
{
	SDL_RenderCopy(Renderer::Instance()->getRenderer(), m_exitTexture, NULL, m_exit);
}
void EndState::processEvents(bool& isRunning)
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
			if (event.button.x > m_exit->x && event.button.x <m_exit->x + m_exit->w
				&&
				event.button.y > m_exit->y && event.button.y < m_exit->y + m_exit->h)
			{
				//std::cout << "Play Button" << std::endl;
				m_stateMachine->changeState(new MenuState(m_cameraDimensions, m_stateMachine));
			}
			break;
		case SDL_MOUSEBUTTONUP:
			//move = false;
			//m_mouseRect->x = event.button.x;
			//m_mouseRect->y = event.button.y;
			break;
		default:
			break;
		}
	}
}
bool EndState::onEnter()
{
	m_exit = new SDL_Rect();
	m_exit->x = m_cameraDimensions.x * 0.8;
	m_exit->y = m_cameraDimensions.y * 0.9;
	m_exit->w = m_cameraDimensions.x * 0.2;
	m_exit->h = m_cameraDimensions.y * 0.1;

	SDL_Surface* m_exitSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_exitTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_exitSurface);

	return true;
}
bool EndState::onExit()
{
	return true;
}