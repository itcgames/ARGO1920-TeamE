#include "GameStateMachine.h"

//Add new state without removing previous state
void GameStateMachine::pushState(GameState *t_state,SDL_Renderer* t_renderer)
{
	m_gameStateSystem.push_back(t_state);
	m_gameStateSystem.back()->onEnter(t_renderer);
}

//remove previous before adding a new state
void GameStateMachine::changeState(GameState *t_state, SDL_Renderer *t_renderer)
{
	if (!m_gameStateSystem.empty())
	{
		if (m_gameStateSystem.back()->getStateID() == t_state->getStateID())
		{
			return;
		}

		m_gameStateSystem.back()->onExit();
		delete m_gameStateSystem.back();
		m_gameStateSystem.pop_back();
	}


	//init it
	t_state->onEnter(t_renderer);

	//push back new state
	m_gameStateSystem.push_back(t_state);
}

//remove a state that is currently being used without deleting another
void GameStateMachine::popState()
{
	if (!m_gameStateSystem.empty())
	{
		if (m_gameStateSystem.back()->onExit())
		{
			delete m_gameStateSystem.back();
			m_gameStateSystem.pop_back();
		}
	}
}

void GameStateMachine::update()
{
	if (!m_gameStateSystem.empty())
	{
		m_gameStateSystem.back()->update();
	}
}

void GameStateMachine::render()
{
	if (!m_gameStateSystem.empty())
	{
		m_gameStateSystem.back()->render();
	}
}
