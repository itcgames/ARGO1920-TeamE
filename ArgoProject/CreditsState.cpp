#include "CreditsState.h"

const std::string CreditsState::m_creditsID = "CREDITS";

CreditsState::CreditsState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
}

void CreditsState::update()
{

}
void CreditsState::render()
{
	for (int i = 0; i < 10; i++)
	{
		m_text[i]->render();
	}
}
void CreditsState::processEvents(bool& isRunning)
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
bool CreditsState::onEnter()
{
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	Abel = TTF_OpenFont("Assets/Font/CopperPlateGothicBold.ttf", m_cameraDimensions.y / 10);

	if (!Abel) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	m_names[0] = "Developers";
	m_names[1] = "Alex O'Toole";
	m_names[2] = "Aoife Powders";
	m_names[3] = "Brandon Seah-Dempsey";
	m_names[4] = "Paul Nolan";
	m_names[5] = "Brian O'Neill";
	m_names[6] = "Designers";
	m_names[7] = "Niall Cullen";
	m_names[8] = "Person 4";
	m_names[9] = "Person 5";
	m_names[10] = "Person 6";
	m_names[11] = "Person 7";


	SDL_Color White = { 255, 255, 255 };

	for (int i = 0; i < 6; i++)
	{
		m_text[i] = new Text(Abel, m_names[i], m_cameraDimensions.x * 0.05, m_cameraDimensions.y * (i * 0.1) + 0.05);
	}
	for (int i = 6; i < 12; i++)
	{
		m_text[i] = new Text(Abel, m_names[i], m_cameraDimensions.x * 0.6, m_cameraDimensions.y * ((i - 6) * 0.1) + 0.05);
	}

	return true;
}
bool CreditsState::onExit()
{
	std::fill_n(m_names, 10, 0);
	m_stateMachine = nullptr;

	for (int i = 0; i < 10; i++)
	{
		m_text[i] = nullptr;
	}
	return true;
}
