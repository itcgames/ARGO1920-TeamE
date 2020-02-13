#include "MenuState.h"

const std::string MenuState::m_menuID = "MENU";

MenuState::MenuState(Vector2 &t_dimensions, GameStateMachine* t_stateMachine)
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
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_optionsButtonTexture, NULL, m_optionsButton);
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_creditsButtonTexture, NULL, m_creditsButton);
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
				//std::cout << "Play Button" << std::endl;
				m_stateMachine->changeState(new CharacterSelectState(m_buttonDimensions,m_stateMachine));
			}
			else if (event.button.x > m_optionsButton->x && event.button.x < m_optionsButton->x + m_optionsButton->w
				&&
				event.button.y > m_optionsButton->y && event.button.y < m_optionsButton->y + m_optionsButton->h)
			{
				//std::cout << "Options Button" << std::endl;
				m_stateMachine->changeState(new OptionsState(m_buttonDimensions,m_stateMachine));
			}
			else if (event.button.x > m_creditsButton->x && event.button.x < m_creditsButton->x + m_creditsButton->w
				&&
				event.button.y > m_creditsButton->y && event.button.y < m_creditsButton->y + m_creditsButton->h)
			{
				//std::cout << "Options Button" << std::endl;
				m_stateMachine->changeState(new CreditsState(m_buttonDimensions, m_stateMachine));
			}
			else if (event.button.x > m_exitButton->x && event.button.x < m_exitButton->x + m_exitButton->w
				&&
				event.button.y > m_exitButton->y && event.button.y < m_exitButton->y + m_exitButton->h)
			{
				//std::cout << "Exit Button" << std::endl;
				isRunning = false;
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
	//std::cout << "Entering Menu State\n";

	m_playButton = new SDL_Rect();
	m_playButton->x = m_buttonDimensions.x * 0.05;
	m_playButton->y = m_buttonDimensions.y * 0.6;
	m_playButton->w = m_buttonDimensions.x * 0.4;
	m_playButton->h = m_buttonDimensions.y * 0.05;

	SDL_Surface* m_playButtonSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_playButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_playButtonSurface);

	m_optionsButton = new SDL_Rect();
	m_optionsButton->x = m_buttonDimensions.x * 0.05;
	m_optionsButton->y = m_buttonDimensions.y * 0.7;
	m_optionsButton->w = m_buttonDimensions.x * 0.4;
	m_optionsButton->h = m_buttonDimensions.y * 0.05;

	SDL_Surface* m_optionsButtonSurface = IMG_Load("Assets/path.png");
	m_optionsButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(),m_optionsButtonSurface);

	m_creditsButton = new SDL_Rect();
	m_creditsButton->x = m_buttonDimensions.x * 0.05;
	m_creditsButton->y = m_buttonDimensions.y * 0.8;
	m_creditsButton->w = m_buttonDimensions.x * 0.4;
	m_creditsButton->h = m_buttonDimensions.y * 0.05;

	SDL_Surface* m_creditsButtonSurface = IMG_Load("Assets/tileTwo.png");
	m_creditsButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_creditsButtonSurface);

	m_exitButton = new SDL_Rect();
	m_exitButton->x = m_buttonDimensions.x * 0.05;
	m_exitButton->y = m_buttonDimensions.y * 0.9;
	m_exitButton->w = m_buttonDimensions.x * 0.4;
	m_exitButton->h = m_buttonDimensions.y * 0.05;

	SDL_Surface* m_exitButtonSurface = IMG_Load("Assets/tile.png");
	m_exitButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_exitButtonSurface);

	return true;
}

bool MenuState::onExit()
{
	m_playButton = nullptr;
	m_playButtonTexture = nullptr;

	m_optionsButton = nullptr;
	m_optionsButtonTexture = nullptr;

	m_exitButton = nullptr;
	m_exitButtonTexture = nullptr;

	//std::cout << "Exiting Menu State\n";
	return true;
}
