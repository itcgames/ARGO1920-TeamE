#include "LoadState.h"

const std::string LoadState::m_loadID = "LOAD";


LoadState::LoadState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
}

void LoadState::update()
{
	if (m_timerCount <= 0)
	{
		m_stateMachine->changeState(new PlayState(m_cameraDimensions, m_stateMachine));
	}
	else
	{
		m_timerCount--;
	}
}

void LoadState::render()
{
	for (int i = 0; i < 2; i++)
	{
		m_text[i]->render();
	}
}

void LoadState::processEvents(bool& isRunning)
{
}

bool LoadState::onEnter()
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

	Loading[0] = "Level Complete!";
	Loading[1] = "Loading Next Level";



	SDL_Color White = { 255, 255, 255 };

	for (int i = 0; i < 2; i++)
	{
		m_text[i] = new Text(Abel, Loading[i], m_cameraDimensions.x * 0.05, m_cameraDimensions.y * (i * 0.1) + 0.05);
	}

	return true;
}

bool LoadState::onExit()
{
	return true;
}
