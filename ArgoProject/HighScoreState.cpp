#include "HighScoreState.h"

const std::string HighScoreState::m_highScoreID = "CREDITS";

HighScoreState::HighScoreState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
}

void HighScoreState::update()
{

}
void HighScoreState::render()
{
	for (int i = 0; i < 10; i++)
	{
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_slotTexture, NULL, m_slotRect[i]);
		SDL_RenderCopy(Render::Instance()->getRenderer(), m_nameTextures[i], NULL, m_nameRects[i]);
	}
}
void HighScoreState::processEvents(bool& isRunning)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			m_stateMachine->changeState(new MenuState(m_cameraDimensions, m_stateMachine));
		}
	}
}
bool HighScoreState::onEnter()
{
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	Sans = TTF_OpenFont("Assets/Font/Abel.ttf", m_cameraDimensions.y / 10);

	if (!Sans) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	m_names[0] = "Brian O'Neill";
	m_names[1] = "Alex O'Toole";
	m_names[2] = "Aoife Powders";
	m_names[3] = "Brandon Seah-Dempsey";
	m_names[4] = "Paul Nolan";
	m_names[5] = "Person 1";
	m_names[6] = "Person 2";
	m_names[7] = "Person 3";
	m_names[8] = "Person 4";
	m_names[9] = "Person 5";

	for (int i = 0; i < 10; i++)
	{
		m_names[i] = std::string(std::to_string(i + 1) + ". " + m_names[i]);
	}

	SDL_Color White = { 255, 255, 255 };


	SDL_Surface* surfaceSlot = IMG_Load("Assets/ecs_text2.png");
	m_slotTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surfaceSlot);

	for (int i = 0; i < 10; i++)
	{
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, m_names[i].c_str(), White);
		m_nameTextures[i] = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surfaceMessage);

		m_nameRects[i] = new SDL_Rect();

		m_nameRects[i]->x = m_cameraDimensions.x * 0.2;
		m_nameRects[i]->y = m_cameraDimensions.y * (i * 0.1) + 0.05;
		m_nameRects[i]->w = m_cameraDimensions.x * 0.6;
		m_nameRects[i]->h = m_cameraDimensions.y * 0.1;
		
		m_slotRect[i] = new SDL_Rect();

		m_slotRect[i]->x = m_cameraDimensions.x * 0.2;
		m_slotRect[i]->y = m_cameraDimensions.y * (i * 0.1) + 0.05;
		m_slotRect[i]->w = m_cameraDimensions.x * 0.6;
		m_slotRect[i]->h = m_cameraDimensions.y * 0.1 - 10;
	}

	return true;
}
bool HighScoreState::onExit()
{
	std::fill_n(m_names, 10, 0);
	//std::fill_n(m_nameRects, 10, 0);
	//std::fill_n(m_nameTextures, 10, 0);
	m_stateMachine = nullptr;

	for (int i = 0; i < 10; i++)
	{
		m_nameRects[i] = nullptr;
		m_nameTextures[i] = nullptr;
	}
	return true;
}
