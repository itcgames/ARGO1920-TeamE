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
	SDL_RenderCopy(Render::Instance()->getRenderer(), m_exitTexture, NULL, m_exitRect);

	for (int i = 0; i < 3; i++)
	{
		m_text[i]->render();
	}
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
			else if (event.button.x > m_exitRect->x && event.button.x < m_exitRect->x + m_exitRect->w
				&&
				event.button.y > m_exitRect->y && event.button.y < m_exitRect->y + m_exitRect->h)
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

bool HostSearchState::onEnter()
{
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	Abel = TTF_OpenFont("Assets/Font/Abel.ttf", m_cameraDimensions.y * 0.3);

	if (!Abel) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	std::string m_texts[2];
	m_texts[0] = "Host";
	m_texts[1] = "Search";

	m_text[0] = new Text(Abel, m_texts[0], m_cameraDimensions.x * 0.3, m_cameraDimensions.y * 0.05);
	m_text[1] = new Text(Abel, m_texts[1], m_cameraDimensions.x * 0.25, m_cameraDimensions.y * 0.45);

	SDL_Color White = { 255, 255, 255 };
	//std::cout << "Entering Menu State\n";

	m_hostRect = new SDL_Rect();
	m_hostRect->x = m_cameraDimensions.x * 0.25;
	m_hostRect->y = m_cameraDimensions.y * 0.1;
	m_hostRect->w = m_cameraDimensions.x * 0.5;
	m_hostRect->h = m_cameraDimensions.y * 0.3;

	SDL_Surface* m_hostSurface = IMG_Load("Assets/Button.png");
	m_hostTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_hostSurface);



	m_searchRect = new SDL_Rect();
	m_searchRect->x = m_cameraDimensions.x * 0.25;
	m_searchRect->y = m_cameraDimensions.y * 0.5;
	m_searchRect->w = m_cameraDimensions.x * 0.5;
	m_searchRect->h = m_cameraDimensions.y * 0.3;

	SDL_Surface* m_searchSurface = IMG_Load("Assets/Button.png");
	m_searchTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_searchSurface);

	m_exitRect = new SDL_Rect();
	m_exitRect->x = m_cameraDimensions.x * (2.5 / 6.0);
	m_exitRect->y = m_cameraDimensions.y * 0.9;
	m_exitRect->w = m_cameraDimensions.x * (1.0 / 6.0);
	m_exitRect->h = m_cameraDimensions.y * 0.1;

	SDL_Surface* m_exitOptionSurface = IMG_Load("Assets/Button.png");
	m_exitTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_exitOptionSurface);
	
	Abel = TTF_OpenFont("Assets/Font/Abel.ttf", m_cameraDimensions.y * 0.1);

	m_text[2] = new Text(Abel, "Return", m_cameraDimensions.x * (2.5 / 6.0), m_cameraDimensions.y * 0.9);

	return true;
}

bool HostSearchState::onExit()
{
	m_hostRect = nullptr;
	SDL_DestroyTexture(m_hostTexture);

	m_searchRect = nullptr;
	SDL_DestroyTexture(m_exitTexture);

	for (int i = 0; i < 2; i++)
	{
		m_text[i]->DestroyText();
	}
	TTF_CloseFont(Abel);
	//std::cout << "Exiting Menu State\n";
	return true;
}
