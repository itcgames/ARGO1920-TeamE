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
				LevelLoader::writeToPlayer("PLAYER_KNIGHT", 200, 200, 4, 0, 0);
				LevelLoader::load(".\\ASSETS\\YAML\\Level1.yaml", m_data);
				data::Instance()->setUpData(m_data);
				data::Instance()->update();
				if (data::Instance()->SINGLEPLAYER)
				{
					m_stateMachine->changeState(new PlayState(m_cameraDimensions, m_stateMachine));
				}
				else
				{
					m_stateMachine->changeState(new MultiplayerState(m_cameraDimensions, m_stateMachine));
				}
			}
			else if (event.button.x > m_dpsOption->x && event.button.x < m_dpsOption->x + m_dpsOption->w
				&&
				event.button.y > m_dpsOption->y && event.button.y < m_dpsOption->y + m_dpsOption->h)
			{
				LevelLoader::writeToPlayer("PLAYER_WARRIOR", 150, 100, 6, 0, 0);
				LevelLoader::load(".\\ASSETS\\YAML\\Level1.yaml", m_data);
				data::Instance()->setUpData(m_data);
				data::Instance()->update();
				if (data::Instance()->SINGLEPLAYER)
				{
					m_stateMachine->changeState(new PlayState(m_cameraDimensions, m_stateMachine));
				}
				else
				{
					m_stateMachine->changeState(new MultiplayerState(m_cameraDimensions, m_stateMachine));
				}
			}
			else if (event.button.x > m_mageOption->x && event.button.x < m_mageOption->x + m_mageOption->w
				&&
				event.button.y > m_mageOption->y && event.button.y < m_mageOption->y + m_mageOption->h)
			{
				LevelLoader::writeToPlayer("PLAYER_MAGE", 100, 200, 8, 0, 0);
				LevelLoader::load(".\\ASSETS\\YAML\\Level1.yaml", m_data);
				data::Instance()->setUpData(m_data);
				data::Instance()->update();
				if (data::Instance()->SINGLEPLAYER)
				{
					m_stateMachine->changeState(new PlayState(m_cameraDimensions, m_stateMachine));
				}
				else
				{
					m_stateMachine->changeState(new MultiplayerState(m_cameraDimensions, m_stateMachine));
				}
			}
			break;
		default:
			break;
		}
	}
}
bool CharacterSelectState::onEnter()
{

	SDL_Surface* characterSelectSurface;

	m_tankOption = new SDL_Rect();
	m_tankOption->x = 0;
	m_tankOption->y = 0;
	m_tankOption->w = m_cameraDimensions.x * (1.0 / 3.0);
	m_tankOption->h = m_cameraDimensions.y;

	characterSelectSurface = IMG_Load("Assets/knightCharacter.png");
	m_tankOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), characterSelectSurface);

	m_dpsOption = new SDL_Rect();
	m_dpsOption->x = m_cameraDimensions.x * (1.0/3.0);
	m_dpsOption->y = 0;
	m_dpsOption->w = m_cameraDimensions.x * (1.0 / 3.0);
	m_dpsOption->h = m_cameraDimensions.y;

	characterSelectSurface = IMG_Load("Assets/warriorCharacter.png");
	m_dpsOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), characterSelectSurface);

	m_mageOption = new SDL_Rect();
	m_mageOption->x = m_cameraDimensions.x * (2.0 / 3.0);;
	m_mageOption->y = 0;
	m_mageOption->w = m_cameraDimensions.x * (1.0 / 3.0);
	m_mageOption->h = m_cameraDimensions.y;

	characterSelectSurface = IMG_Load("Assets/wizardCharacter.png");
	m_mageOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), characterSelectSurface);

	m_exitOption = new SDL_Rect();
	m_exitOption->x = m_cameraDimensions.x * 0.85;
	m_exitOption->y = m_cameraDimensions.y * 0.9;
	m_exitOption->w = m_cameraDimensions.x * (1.0 / 6.0);
	m_exitOption->h = m_cameraDimensions.y * 0.1;

	characterSelectSurface = IMG_Load("Assets/ReturnButton.png");
	m_exitOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), characterSelectSurface);

	SDL_FreeSurface(characterSelectSurface);

	return true;
}
bool CharacterSelectState::onExit()
{
	SDL_DestroyTexture(m_tankOptionTexture);
	SDL_DestroyTexture(m_dpsOptionTexture);
	SDL_DestroyTexture(m_mageOptionTexture);
	SDL_DestroyTexture(m_exitOptionTexture);

	//delete m_tankOption;
	//delete m_mageOption;
	//delete m_dpsOption;
	//delete m_exitOption;
	return true;
}
