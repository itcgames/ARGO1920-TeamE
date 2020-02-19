#include "CharacterSelectState.h"

const std::string CharacterSelectState::m_characterSelectID = "CHARACTERSELECT";

CharacterSelectState::CharacterSelectState(Vector2& t_screenDimensions,GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
}

void CharacterSelectState::update()
{

}
void CharacterSelectState::render()
{
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_tankOptionTexture, NULL, m_tankOption);
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_dpsOptionTexture, NULL, m_dpsOption);
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_mageOptionTexture, NULL, m_mageOption);
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_exitOptionTexture, NULL, m_exitOption);

	for (int i = 0; i < 4; i++)
	{
		m_text[i]->render();
	}
}
void CharacterSelectState::processEvents(bool& isRunning)
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
			if (event.button.x > m_exitOption->x && event.button.x <m_exitOption->x + m_exitOption->w
				&&
				event.button.y > m_exitOption->y && event.button.y < m_exitOption->y + m_exitOption->h)
			{
				m_stateMachine->changeState(new MenuState(m_cameraDimensions, m_stateMachine));
			}
			else if (event.button.x > m_tankOption->x && event.button.x <m_tankOption->x + m_tankOption->w
				&&
				event.button.y > m_tankOption->y && event.button.y < m_tankOption->y + m_tankOption->h)
			{
				//std::cout << "Play Button" << std::endl;
				LevelLoader::writeToPlayer("PLAYER_KNIGHT", 200, 200, 2, 0, 0);
				LevelLoader::load(".\\ASSETS\\YAML\\Level1.yaml", m_data);
				data::Instance()->setUpData(m_data);
				m_stateMachine->changeState(new PlayState(m_cameraDimensions,m_stateMachine));
			}
			else if (event.button.x > m_dpsOption->x && event.button.x < m_dpsOption->x + m_dpsOption->w
				&&
				event.button.y > m_dpsOption->y && event.button.y < m_dpsOption->y + m_dpsOption->h)
			{
				LevelLoader::writeToPlayer("PLAYER_WARRIOR", 150, 100, 5, 0, 0);
				LevelLoader::load(".\\ASSETS\\YAML\\Level1.yaml", m_data);
				data::Instance()->setUpData(m_data);
				m_stateMachine->changeState(new PlayState(m_cameraDimensions,m_stateMachine));
			}
			else if (event.button.x > m_mageOption->x && event.button.x < m_mageOption->x + m_mageOption->w
				&&
				event.button.y > m_mageOption->y && event.button.y < m_mageOption->y + m_mageOption->h)
			{
				LevelLoader::writeToPlayer("PLAYER_MAGE", 100, 200, 7, 0, 0);
				LevelLoader::load(".\\ASSETS\\YAML\\Level1.yaml", m_data);
				data::Instance()->setUpData(m_data);
				m_stateMachine->changeState(new PlayState(m_cameraDimensions,m_stateMachine));
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
bool CharacterSelectState::onEnter()
{
	std::string m_classNames[3];

	m_classNames[0] = "Knight";
	m_classNames[1] = "Warrior";
	m_classNames[2] = "Mage";

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	Abel = TTF_OpenFont("Assets/Font/Abel.ttf", m_cameraDimensions.y / 10);

	if (!Abel) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	SDL_Surface* surfaceMessage;
	SDL_Color White = { 255, 255, 255 };

	for (int i = 0; i < 3; i++)
	{
		m_textRects[i] = new SDL_Rect();
		TTF_SizeText(Abel, m_classNames[i].c_str(), &m_textRects[i]->w, &m_textRects[i]->h);
		m_text[i] = new Text(Abel, m_classNames[i], m_cameraDimensions.x * ((1.0f + 2.0f * i) / 6.0f) - m_textRects[i]->w / 2, m_cameraDimensions.y * 0.2);
	}

	m_tankOption = new SDL_Rect();
	m_tankOption->x = 0;
	m_tankOption->y = 0;
	m_tankOption->w = m_cameraDimensions.x * (1.0 / 3.0);
	m_tankOption->h = m_cameraDimensions.y;

	SDL_Surface* m_tankOptionSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_tankOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_tankOptionSurface);

	m_dpsOption = new SDL_Rect();
	m_dpsOption->x = m_cameraDimensions.x * (1.0/3.0);
	m_dpsOption->y = 0;
	m_dpsOption->w = m_cameraDimensions.x * (1.0 / 3.0);
	m_dpsOption->h = m_cameraDimensions.y;

	SDL_Surface* m_dpsOptionSurface = IMG_Load("Assets/Health.png");
	m_dpsOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_dpsOptionSurface);

	m_mageOption = new SDL_Rect();
	m_mageOption->x = m_cameraDimensions.x * (2.0 / 3.0);;
	m_mageOption->y = 0;
	m_mageOption->w = m_cameraDimensions.x * (1.0 / 3.0);
	m_mageOption->h = m_cameraDimensions.y;

	SDL_Surface* m_mageOptionSurface = IMG_Load("Assets/Mana.png");
	m_mageOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_mageOptionSurface);

	m_exitOption = new SDL_Rect();
	m_exitOption->x = m_cameraDimensions.x * (2.5 / 6.0);
	m_exitOption->y = m_cameraDimensions.y * 0.9;
	m_exitOption->w = m_cameraDimensions.x * (1.0 / 6.0);
	m_exitOption->h = m_cameraDimensions.y * 0.1;

	SDL_Surface* m_exitOptionSurface = IMG_Load("Assets/Stamina.png");
	m_exitOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_exitOptionSurface);

	m_text[3] = new Text(Abel, "Return", m_cameraDimensions.x * (2.5 / 6.0), m_cameraDimensions.y * 0.9);

	return true;
}
bool CharacterSelectState::onExit()
{
	return true;
}