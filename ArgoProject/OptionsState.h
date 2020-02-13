#ifndef OPTIONSSTATE
#define OPTIONSSTATE
#include "GameState.h"
#include "MenuState.h"
class OptionsState :
	public GameState
{
public:
	OptionsState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine);

	virtual void update();
	virtual void render();
	virtual void processEvents(bool& isRunning);
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_optionsID; };

private:
	Vector2 m_cameraDimensions;

	static const std::string  m_optionsID;

	SDL_Rect* m_exitButton;
	SDL_Texture* m_exitButtonTexture;

	GameStateMachine* m_stateMachine;
};

#endif