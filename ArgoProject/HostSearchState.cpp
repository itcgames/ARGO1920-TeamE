#include "HostSearchState.h"
const std::string HostSearchState::m_hostSearchID = "HostSearch";

HostSearchState::HostSearchState(Vector2& t_dimensions, GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_dimensions;
	m_stateMachine = t_stateMachine;
}


void HostSearchState::update()
{


}

void HostSearchState::render()
{
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_hostTexture, NULL, m_hostRect);
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_searchTexture, NULL, m_searchRect);
}

void HostSearchState::processEvents(bool& isRunning)
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
			if (event.button.x > m_hostRect->x && event.button.x < m_hostRect->x + m_hostRect->w
				&&
				event.button.y > m_hostRect->y && event.button.y < m_hostRect->y + m_hostRect->h)
			{
				//std::cout << "Play Button" << std::endl;
				data::Instance()->HOST = true;
				m_stateMachine->changeState(new CharacterSelectState(m_cameraDimensions, m_stateMachine));
			}
			else if (event.button.x > m_searchRect->x && event.button.x < m_searchRect->x + m_searchRect->w
				&&
				event.button.y > m_searchRect->y && event.button.y < m_searchRect->y + m_searchRect->h)
			{
				//std::cout << "Play Button" << std::endl;
				data::Instance()->HOST = false;
				m_stateMachine->changeState(new CharacterSelectState(m_cameraDimensions, m_stateMachine));
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

bool HostSearchState::onEnter()
{
	//std::cout << "Entering Menu State\n";

	m_hostRect = new SDL_Rect();
	m_hostRect->x = m_cameraDimensions.x * 0.1;
	m_hostRect->y = m_cameraDimensions.y * 0.1;
	m_hostRect->w = m_cameraDimensions.x * 0.8;
	m_hostRect->h = m_cameraDimensions.y * 0.3;

	SDL_Surface* m_hostSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_hostTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_hostSurface);

	m_searchRect = new SDL_Rect();
	m_searchRect->x = m_cameraDimensions.x * 0.1;
	m_searchRect->y = m_cameraDimensions.y * 0.6;
	m_searchRect->w = m_cameraDimensions.x * 0.8;
	m_searchRect->h = m_cameraDimensions.y * 0.3;

	SDL_Surface* m_searchSurface = IMG_Load("Assets/ecs_text2.png");
	m_searchTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_searchSurface);


	return true;
}

bool HostSearchState::onExit()
{
	m_hostRect = nullptr;
	m_hostTexture = nullptr;

	m_searchRect = nullptr;
	m_searchTexture = nullptr;

	//std::cout << "Exiting Menu State\n";
	return true;
}
