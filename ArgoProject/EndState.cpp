#include "EndState.h"

const std::string EndState::m_endID = "END";

EndState::EndState(Vector2& t_screenDimensions,GameStateMachine* t_stateMachine)
{
	m_cameraDimensions = t_screenDimensions;
	m_stateMachine = t_stateMachine;
}

void EndState::update()
{

}
void EndState::render()
{
	SDL_RenderCopy(Renderer::Instance()->getRenderer(), m_exitTexture, NULL, m_exit);
	for (int i = 0; i < m_keyboard.size(); i++)
	{
		SDL_RenderCopy(Renderer::Instance()->getRenderer(), m_keyboardTexture[i], NULL, m_keyboard[i]);
	}
	m_message->render();
}
void EndState::processEvents(bool& isRunning)
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
			for (int i = 0; i < 26; i++)
			{
				if (event.button.x > m_keyboard[i]->x && event.button.x <m_keyboard[i]->x + m_keyboard[i]->w
					&&
					event.button.y > m_keyboard[i]->y && event.button.y < m_keyboard[i]->y + m_keyboard[i]->h)
				{
					data::Instance()->playerName += m_keyValues[i];
				}
			}
			if (event.button.x > m_keyboard[26]->x && event.button.x <m_keyboard[26]->x + m_keyboard[26]->w
				&&
				event.button.y > m_keyboard[26]->y && event.button.y < m_keyboard[26]->y + m_keyboard[26]->h)
			{
				data::Instance()->playerName += " ";
			}
			if (event.button.x > m_keyboard[27]->x && event.button.x <m_keyboard[27]->x + m_keyboard[27]->w
				&&
				event.button.y > m_keyboard[27]->y && event.button.y < m_keyboard[27]->y + m_keyboard[27]->h)
			{
				data::Instance()->playerName.pop_back();
			}
			if (event.button.x > m_exit->x && event.button.x <m_exit->x + m_exit->w
				&&
				event.button.y > m_exit->y && event.button.y < m_exit->y + m_exit->h)
			{
				//std::cout << "Play Button" << std::endl;
				data::Instance()->newScore();
				LevelLoader::load(".\\ASSETS\\YAML\\Level1.yaml", m_data);
				data::Instance()->setUpData(m_data);
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
bool EndState::onEnter()
{
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	Abel = TTF_OpenFont("Assets/Font/Abel.ttf", m_cameraDimensions.y / 20);

	if (!Abel) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	for (int i = 0; i < 5; i++)
	{
		m_message = new Text(Abel, "Enter Your Name", m_cameraDimensions.x * 0.28, m_cameraDimensions.y * 0.02);
	}
	m_exit = new SDL_Rect();
	m_exit->x = m_cameraDimensions.x * 0.8;
	m_exit->y = m_cameraDimensions.y * 0.9;
	m_exit->w = m_cameraDimensions.x * 0.2;
	m_exit->h = m_cameraDimensions.y * 0.1;

	SDL_Surface* m_exitSurface = IMG_Load("Assets/miniMapPlaceHolder.png");
	m_exitTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_exitSurface);

	std::stringstream ss;
	std::string temp;
	for (int i = 0; i < 26; i++)
	{
		ss << char(65 + (i));
		ss >> temp;
		m_keyValues.push_back(temp);
		ss.clear();
	}

	float x = 0.1;
	for (int i = 0; i < 5; i++)
	{
		CreateKeyBoardRow(x, 0.1);
		x += 0.110;
	}
	x = 0.1;
	for (int i = 0; i < 5; i++)
	{
		CreateKeyBoardRow(x, 0.210);
		x += 0.110;
	}
	x = 0.1;
	for (int i = 0; i < 5; i++)
	{
		CreateKeyBoardRow(x, 0.320);
		x += 0.110;
	}
	x = 0.1;
	for (int i = 0; i < 5; i++)
	{
		CreateKeyBoardRow(x, 0.430);
		x += 0.110;
	}
	x = 0.1;
	for (int i = 0; i < 5; i++)
	{
		CreateKeyBoardRow(x, 0.540);
		x += 0.110;
	}
	x = 0.1;
	for (int i = 0; i < 1; i++)
	{
		CreateKeyBoardRow(x, 0.650);
	}
	CreateKey(0.210, 0.650);
	CreateKey(0.430, 0.650);
	return true;
}
bool EndState::onExit()
{
	return true;
}

void EndState::CreateKeyBoardRow(float num, float num2)
{
	m_keyboard.push_back(new SDL_Rect());
	m_keyboard.back()->x = m_cameraDimensions.x * (num);
	m_keyboard.back()->y = m_cameraDimensions.y * (num2);
	m_keyboard.back()->w = m_cameraDimensions.x * (0.1);
	m_keyboard.back()->h = m_cameraDimensions.y * (0.1);
	SDL_Surface* m_keyboardSurface = IMG_Load("Assets/ecs_text.png");
	m_keyboardTexture.push_back(SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_keyboardSurface));
}

void EndState::CreateKey(float num, float num2)
{
	m_keyboard.push_back(new SDL_Rect());
	m_keyboard.back()->x = m_cameraDimensions.x * (num);
	m_keyboard.back()->y = m_cameraDimensions.y * (num2);
	m_keyboard.back()->w = m_cameraDimensions.x * (0.210);
	m_keyboard.back()->h = m_cameraDimensions.y * (0.1);
	SDL_Surface* m_keyboardSurface = IMG_Load("Assets/ecs_text.png");
	m_keyboardTexture.push_back(SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), m_keyboardSurface));
}
