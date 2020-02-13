#ifndef ENDSTATE
#define ENDSTATE
#include "GameState.h"
#include "MenuState.h"
class EndState :
	public GameState
{
public:
	EndState(Vector2& t_screenDimensions,GameStateMachine* t_stateMachine);

	virtual void update();
	virtual void render();
	virtual void processEvents(bool& isRunning);
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_endID; };

private:
	Vector2 m_cameraDimensions;

	static const std::string  m_endID;

	GameStateMachine* m_stateMachine;

	SDL_Rect* m_exit;
	SDL_Texture* m_exitTexture;
};

#endif