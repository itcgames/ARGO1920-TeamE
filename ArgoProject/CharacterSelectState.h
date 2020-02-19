#ifndef CHARACTERSELECTSTATE
#define CHARACTERSELECTSTATE
#include "GameState.h"
#include "PlayState.h"
#include "Data.h"
#include "LevelLoader.h"
class CharacterSelectState :
	public GameState
{
public:
	CharacterSelectState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine);

	virtual void update();
	virtual void render();
	virtual void processEvents(bool& isRunning);
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_characterSelectID; };

private:
	void cameraSetup();
	void collisions();

	Vector2 m_cameraDimensions;

	static const std::string  m_characterSelectID;

	SDL_Rect* m_tankOption;
	SDL_Texture* m_tankOptionTexture;

	SDL_Rect* m_dpsOption;
	SDL_Texture* m_dpsOptionTexture;

	SDL_Rect* m_mageOption;
	SDL_Texture* m_mageOptionTexture;

	GameStateMachine* m_stateMachine;
	GameData m_data;
};

#endif