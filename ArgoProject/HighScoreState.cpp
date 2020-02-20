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
		if(m_score[i] > 0)
		{ 
			SDL_RenderCopy(Render::Instance()->getRenderer(), m_slotTexture, NULL, m_slotRect[i]);
			//SDL_RenderCopy(Render::Instance()->getRenderer(), m_nameTextures[i], NULL, m_nameRects[i]);
			m_text[i]->render();
		}
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

	Abel = TTF_OpenFont("Assets/Font/Abel.ttf", m_cameraDimensions.y / 10);

	if (!Abel) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	for (int i = 0; i < 10; i++)
	{
		m_names[i] = data::Instance()->getData().m_scores.at(i).m_name;
		m_score[i] = data::Instance()->getData().m_scores.at(i).m_score;
		m_scoreString[i] = std::to_string(m_score[i]);
	}

	long int temp = 0;
	std::string nameTemp = "";
	for (int i = 0; i < 10; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (m_scoreString[j] > m_scoreString[i])
			{
				temp = m_score[i];
				nameTemp = m_names[i];
				m_scoreString[i] = m_scoreString[j];
				m_score[i] = m_score[j];
				m_names[i] = m_names[j];
				m_scoreString[j] = std::to_string(temp);
				m_score[j] = temp;
				m_names[j] = nameTemp;
			}
		}
		m_display[i] = std::string(std::to_string(i + 1) + ". " + m_names[i] + " - " + m_scoreString[i]);
	}

	SDL_Color White = { 255, 255, 255 };


	SDL_Surface* surfaceSlot = IMG_Load("Assets/ecs_text2.png");
	m_slotTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surfaceSlot);

	for (int i = 0; i < 10; i++)
	{
		m_text[i] = new Text(Abel, m_display[i], m_cameraDimensions.x * 0.2, m_cameraDimensions.y * ((i * 0.1)));

		m_slotRect[i] = new SDL_Rect();

		m_slotRect[i]->x = m_cameraDimensions.x * 0.2;
		m_slotRect[i]->y = m_cameraDimensions.y * ((i * 0.1) + 0.015);
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
		m_text[i] = nullptr;
	}
	return true;
}

void HighScoreState::writeScores()
{
	long int temp = 0;
	std::string nameTemp = "";
	for (int i = 0; i < 10; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (m_scoreString[j] > m_scoreString[i])
			{
				temp = m_score[i];
				nameTemp = m_names[i];
				m_scoreString[i] = m_scoreString[j];
				m_score[i] = m_score[j];
				m_names[i] = m_names[j];
				m_scoreString[j] = std::to_string(temp);
				m_score[j] = temp;
				m_names[j] = nameTemp;
			}
		}
		m_names[i] = m_names[i];
		LevelLoader::write(m_names, m_score);
	}
}

void HighScoreState::newScore(int t_newScore, std::string t_newName)
{
	int lowest = m_score[0];
	int lowestIndex = 0;
	for (int i = 1; i < 10; i++)
	{
		if (m_score[i] < lowest)
		{
			lowest = m_score[i];
			lowestIndex = i;
		}
	}
	m_scoreString[lowestIndex] = t_newScore;
	m_names[lowestIndex] = t_newName;

	writeScores();
}
