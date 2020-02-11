#include "MenuState.h"

const std::string MenuState::m_menuID = "MENU";

MenuState::MenuState(Vector2 t_dimensions, GameStateMachine* t_stateMachine)
{
	m_buttonDimensions = t_dimensions;
	m_stateMachine = t_stateMachine;
}


void MenuState::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 9));

}

void MenuState::render()
{
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_playButtonTexture, NULL, m_playButton);
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_exitButtonTexture, NULL, m_exitButton);
}

void MenuState::processEvents(bool &isRunning)
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
			if (event.button.x > m_playButton->x && event.button.x < m_playButton->x + m_playButton->w
				&&
				event.button.y > m_playButton->y && event.button.y < m_playButton->y + m_playButton->h)
			{
				std::cout << "Play Button" << std::endl;
				m_stateMachine->changeState(new PlayState(m_buttonDimensions));
			}
			else if (event.button.x > m_exitButton->x && event.button.x < m_exitButton->x + m_exitButton->w
				&&
				event.button.y > m_exitButton->y && event.button.y < m_exitButton->y + m_exitButton->h)
			{
				std::cout << "Exit Button" << std::endl;
				isRunning = false;
				std::cout << isRunning << std::endl;
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

bool MenuState::onEnter()
{
	std::cout << "Entering Menu State\n";

	m_playButton = new SDL_Rect();
	m_playButton->x = m_buttonDimensions.x * 0.1;
	m_playButton->y = m_buttonDimensions.y * 0.1;
	m_playButton->w = m_buttonDimensions.x * 0.8;
	m_playButton->h = m_buttonDimensions.y * 0.3;

	SDL_Surface* m_playButtonSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_playButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_playButtonSurface);

	m_exitButton = new SDL_Rect();
	m_exitButton->x = m_buttonDimensions.x * 0.1;
	m_exitButton->y = m_buttonDimensions.y / 2 + m_buttonDimensions.y * 0.1;
	m_exitButton->w = m_buttonDimensions.x * 0.8;
	m_exitButton->h = m_buttonDimensions.y * 0.3;

	SDL_Surface* m_exitButtonSurface = IMG_Load("Assets/tile.png");
	m_exitButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_exitButtonSurface);

	return true;
}

bool MenuState::onExit()
{
	m_playButton = nullptr;
	m_playButtonTexture = nullptr;

	m_exitButton = nullptr;
	m_exitButtonTexture = nullptr;

	std::cout << "Exiting Menu State\n";
	return true;
}
