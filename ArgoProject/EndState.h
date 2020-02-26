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
	std::vector<SDL_Rect*> m_keyboard;
	SDL_Texture* m_exitTexture;
	std::vector<SDL_Texture*> m_keyboardTexture;
	std::vector<std::string> m_keyValues;
	GameData m_data;
	void CreateKeyBoardRow(float num, float num2, float num3, float num4);
	void CreateKey(float num, float num2);
	TTF_Font* Abel;
	Text* m_message;
	std::vector<Text*> m_keyText;
};

#endif