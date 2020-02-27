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
		m_text[i]->render();
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
				m_stateMachine->changeState(new CharacterSelectState(m_buttonDimensions, m_stateMachine));
			}
			else if (event.button.x > m_optionsButton->x && event.button.x < m_optionsButton->x + m_optionsButton->w
				&&
				event.button.y > m_optionsButton->y && event.button.y < m_optionsButton->y + m_optionsButton->h)
			{
				//std::cout << "Options Button" << std::endl;
				m_stateMachine->changeState(new CreditsState(m_buttonDimensions, m_stateMachine));
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

	Abel = TTF_OpenFont("Assets/Font/CopperPlateGothicBold.ttf", m_buttonDimensions.y / 20);

	if (!Abel) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	std::string m_name[5];
	m_name[0] = "Singleplayer";
	m_name[1] = "Multiplayer";
	m_name[2] = "Credits";
	m_name[3] = "Highscores";
	m_name[4] = "Exit";

	for (int i = 0; i < 5; i++)
	{
		m_text[i] = new Text(Abel, m_name[i], m_buttonDimensions.x * 0.05, m_buttonDimensions.y * (0.49 + (float(i) / 10.0f)));
	}
	//std::cout << "Entering Menu State\n";

	m_singlePlayerButton = new SDL_Rect();
	m_singlePlayerButton->x = m_buttonDimensions.x * 0.02;
	m_singlePlayerButton->y = m_buttonDimensions.y * 0.495;
	m_singlePlayerButton->w = m_buttonDimensions.x * 0.3;
	m_singlePlayerButton->h = m_buttonDimensions.y * 0.06;


	SDL_Surface* menuSurface = IMG_Load("Assets/Button.png");
	m_singlePlayerButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), menuSurface);

	m_multiPlayerButton = new SDL_Rect();
	m_multiPlayerButton->x = m_buttonDimensions.x * 0.02;
	m_multiPlayerButton->y = m_buttonDimensions.y * 0.595;
	m_multiPlayerButton->w = m_buttonDimensions.x * 0.3;
	m_multiPlayerButton->h = m_buttonDimensions.y * 0.06;

	menuSurface = IMG_Load("Assets/Button.png");
	m_multiPlayerButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), menuSurface);

	m_optionsButton = new SDL_Rect();
	m_optionsButton->x = m_buttonDimensions.x * 0.02;
	m_optionsButton->y = m_buttonDimensions.y * 0.695;
	m_optionsButton->w = m_buttonDimensions.x * 0.3;
	m_optionsButton->h = m_buttonDimensions.y * 0.06;

	menuSurface = IMG_Load("Assets/Button.png");
	m_optionsButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), menuSurface);

	m_creditsButton = new SDL_Rect();
	m_creditsButton->x = m_buttonDimensions.x * 0.02;
	m_creditsButton->y = m_buttonDimensions.y * 0.795;
	m_creditsButton->w = m_buttonDimensions.x * 0.3;
	m_creditsButton->h = m_buttonDimensions.y * 0.06;

	menuSurface = IMG_Load("Assets/Button.png");
	m_creditsButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), menuSurface);

	m_exitButton = new SDL_Rect();
	m_exitButton->x = m_buttonDimensions.x * 0.02;
	m_exitButton->y = m_buttonDimensions.y * 0.895;
	m_exitButton->w = m_buttonDimensions.x * 0.2;
	m_exitButton->h = m_buttonDimensions.y * 0.06;

	menuSurface = IMG_Load("Assets/Button.png");
	m_exitButtonTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), menuSurface);

	SDL_FreeSurface(menuSurface);
	return true;
}

bool MenuState::onExit()
{
	SDL_DestroyTexture(m_singlePlayerButtonTexture);
	SDL_DestroyTexture(m_multiPlayerButtonTexture);
	SDL_DestroyTexture(m_optionsButtonTexture);
	SDL_DestroyTexture(m_creditsButtonTexture);
	SDL_DestroyTexture(m_exitButtonTexture);

	for (int i = 0; i < 5; i++)
	{
		m_text[i]->DestroyText();
	}
	TTF_CloseFont(Abel);

	return true;
}