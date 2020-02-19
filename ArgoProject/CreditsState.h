#ifndef CREDITSSTATE
#define CREDITSSTATE
#include "GameState.h"
#include "MenuState.h"
#include <array>
class CreditsState :
	public GameState
{
public:
	CreditsState(Vector2& t_screenDimensions,GameStateMachine* t_stateMachine);

	virtual void update();
	virtual void render();
	virtual void processEvents(bool& isRunning);
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_creditsID; };

private:
	Vector2 m_cameraDimensions;

	static const std::string  m_creditsID;

	std::string m_names[10];

	SDL_Rect* m_nameRects[10];
	SDL_Texture* m_nameTextures[10];
	
	TTF_Font* Abel;

	GameStateMachine* m_stateMachine;
};

#endif