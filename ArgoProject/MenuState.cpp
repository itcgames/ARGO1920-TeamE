#include "MenuState.h"

const std::string MenuState::m_menuID = "MENU";

MenuState::MenuState(Vector2& t_dimensions, GameStateMachine* t_stateMachine)
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
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_singlePlayerButtonTexture, NULL, m_singlePlayerButton);
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_multiPlayerButtonTexture, NULL, m_multiPlayerButton);
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_optionsButtonTexture, NULL, m_optionsButton);
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_creditsButtonTexture, NULL, m_creditsButton);
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_exitButtonTexture, NULL, m_exitButton);

	for (int i = 0; i < 5; i++)
	{
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_nameTextures[i], NULL, m_nameRects[i]);
	}
}

void MenuState::processEvents(bool& isRunning)
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
			if (event.button.x > m_singlePlayerButton->x && event.button.x < m_singlePlayerButton->x + m_singlePlayerButton->w
				&&
				event.button.y > m_singlePlayerButton->y && event.button.y < m_singlePlayerButton->y + m_singlePlayerButton->h)
			{
				//std::cout << "Play Button" << std::endl;
				data::Instance()->SINGLEPLAYER = true;
				m_stateMachine->changeState(new CharacterSelectState(m_buttonDimensions, m_stateMachine));
			}
			else if (event.button.x > m_multiPlayerButton->x && event.button.x < m_multiPlayerButton->x + m_multiPlayerButton->w
				&&
				event.button.y > m_multiPlayerButton->y && event.button.y < m_multiPlayerButton->y + m_multiPlayerButton->h)
			{
				//std::cout << "Play Button" << std::endl;
				data::Instance()->SINGLEPLAYER = false;
				m_stateMachine->changeState(new HostSearchState(m_buttonDimensions, m_stateMachine));
			}
			else if (event.button.x > m_optionsButton->x && event.button.x < m_optionsButton->x + m_optionsButton->w
				&&
				event.button.y > m_optionsButton->y && event.button.y < m_optionsButton->y + m_optionsButton->h)
			{
				//std::cout << "Options Button" << std::endl;
				m_stateMachine->changeState(new OptionsState(m_buttonDimensions, m_stateMachine));
			}
			else if (event.button.x > m_creditsButton->x && event.button.x < m_creditsButton->x + m_creditsButton->w
				&&
				event.button.y > m_creditsButton->y && event.button.y < m_creditsButton->y + m_creditsButton->h)
			{
				//std::cout << "Options Button" << std::endl;
				m_stateMachine->changeState(new HighScoreState(m_buttonDimensions, m_stateMachine));
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
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	Abel = TTF_OpenFont("Assets/Font/Abel.ttf", m_buttonDimensions.y / 20);

	if (!Abel) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	for (int i = 0; i < 5; i++)
	{
		m_nameRects[i] = new SDL_Rect();

		m_nameRects[i]->x = m_buttonDimensions.x * 0.05;
		m_nameRects[i]->y = m_buttonDimensions.y * (0.49 + (float(i) / 10.0f));
	}

	SDL_Color White = { 255, 255, 255 };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Abel, "Singleplayer", White);
	m_nameTextures[0] = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Abel, "Multiplayer", White);
	m_nameTextures[1] = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Abel, "Options", White);
	m_nameTextures[2] = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Abel, "Credits", White);
	m_nameTextures[3] = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surfaceMessage);

	surfaceMessage = TTF_RenderText_Solid(Abel, "Exit", White);
	m_nameTextures[4] = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surfaceMessage);
	//std::cout << "Entering Menu State\n";

	m_singlePlayerButton = new SDL_Rect();
	m_singlePlayerButton->x = m_buttonDimensions.x * 0.05;
	m_singlePlayerButton->y = m_buttonDimensions.y * 0.5;
	m_singlePlayerButton->w = m_buttonDimensions.x * 0.4;
	m_singlePlayerButton->h = m_buttonDimensions.y * 0.05;

	TTF_SizeText(Abel, "Singleplayer", &m_nameRects[0]->w, &m_nameRects[0]->h);

	SDL_Surface* m_singlePlayerButtonSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_singlePlayerButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_singlePlayerButtonSurface);

	m_multiPlayerButton = new SDL_Rect();
	m_multiPlayerButton->x = m_buttonDimensions.x * 0.05;
	m_multiPlayerButton->y = m_buttonDimensions.y * 0.6;
	m_multiPlayerButton->w = m_buttonDimensions.x * 0.4;
	m_multiPlayerButton->h = m_buttonDimensions.y * 0.05;

	TTF_SizeText(Abel, "Multiplayer", &m_nameRects[1]->w, &m_nameRects[1]->h);

	SDL_Surface* m_multiPlayerButtonSurface = IMG_Load("Assets/ecs_text2.png");
	m_multiPlayerButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_multiPlayerButtonSurface);

	m_optionsButton = new SDL_Rect();
	m_optionsButton->x = m_buttonDimensions.x * 0.05;
	m_optionsButton->y = m_buttonDimensions.y * 0.7;
	m_optionsButton->w = m_buttonDimensions.x * 0.4;
	m_optionsButton->h = m_buttonDimensions.y * 0.05;

	TTF_SizeText(Abel, "Options", &m_nameRects[2]->w, &m_nameRects[2]->h);

	SDL_Surface* m_optionsButtonSurface = IMG_Load("Assets/Health.png");
	m_optionsButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_optionsButtonSurface);

	m_creditsButton = new SDL_Rect();
	m_creditsButton->x = m_buttonDimensions.x * 0.05;
	m_creditsButton->y = m_buttonDimensions.y * 0.8;
	m_creditsButton->w = m_buttonDimensions.x * 0.4;
	m_creditsButton->h = m_buttonDimensions.y * 0.05;

	TTF_SizeText(Abel, "Credits", &m_nameRects[3]->w, &m_nameRects[3]->h);

	SDL_Surface* m_creditsButtonSurface = IMG_Load("Assets/Mana.png");
	m_creditsButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_creditsButtonSurface);

	m_exitButton = new SDL_Rect();
	m_exitButton->x = m_buttonDimensions.x * 0.05;
	m_exitButton->y = m_buttonDimensions.y * 0.9;
	m_exitButton->w = m_buttonDimensions.x * 0.4;
	m_exitButton->h = m_buttonDimensions.y * 0.05;

	TTF_SizeText(Abel, "Exit", &m_nameRects[4]->w, &m_nameRects[4]->h);

	SDL_Surface* m_exitButtonSurface = IMG_Load("Assets/Stamina.png");
	m_exitButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_exitButtonSurface);

	return true;
}

bool MenuState::onExit()
{
	m_singlePlayerButton = nullptr;
	m_singlePlayerButtonTexture = nullptr;

	m_optionsButton = nullptr;
	m_optionsButtonTexture = nullptr;

	m_exitButton = nullptr;
	m_exitButtonTexture = nullptr;

	//std::cout << "Exiting Menu State\n";
	return true;
}