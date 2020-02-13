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
			if (event.button.x > m_tankOption->x && event.button.x <m_tankOption->x + m_tankOption->w
				&&
				event.button.y > m_tankOption->y && event.button.y < m_tankOption->y + m_tankOption->h)
			{
				//std::cout << "Play Button" << std::endl;
				m_stateMachine->changeState(new PlayState(m_cameraDimensions,m_stateMachine));
			}
			else if (event.button.x > m_dpsOption->x && event.button.x < m_dpsOption->x + m_dpsOption->w
				&&
				event.button.y > m_dpsOption->y && event.button.y < m_dpsOption->y + m_dpsOption->h)
			{
				m_stateMachine->changeState(new PlayState(m_cameraDimensions,m_stateMachine));
			}
			else if (event.button.x > m_mageOption->x && event.button.x < m_mageOption->x + m_mageOption->w
				&&
				event.button.y > m_mageOption->y && event.button.y < m_mageOption->y + m_mageOption->h)
			{
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

	SDL_Surface* m_dpsOptionSurface = IMG_Load("Assets/tile.png");
	m_dpsOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_dpsOptionSurface);

	m_mageOption = new SDL_Rect();
	m_mageOption->x = m_cameraDimensions.x * (2.0 / 3.0);;
	m_mageOption->y = 0;
	m_mageOption->w = m_cameraDimensions.x * (1.0 / 3.0);
	m_mageOption->h = m_cameraDimensions.y;

	SDL_Surface* m_mageOptionSurface = IMG_Load("Assets/tileTwo.png");
	m_mageOptionTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_mageOptionSurface);

	return true;
}
bool CharacterSelectState::onExit()
{
	return true;
}