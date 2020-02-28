#ifndef PLAYSTATE
#define PLAYSTATE
#include "ParticleSystem.h"
#include "GameState.h"
#include "EndState.h"
#include "LoadState.h"
#include "SDL.h"
#include "Data.h"
#include "Pickup.h"
#include "CollisionSystem.h"
#include "BehaviourTreeSystem.h"
#include "Map.h"
#include "Server.h"
#include <vector>
#include "Client.h"
#include "HUD.h"
#include <memory>
#include "IEnemy.h"
#include "FactoryEnemy.h"
#include "IPlayer.h"
#include "FactoryPlayer.h"
#include "Audio.h"
#include "PopUpText.h"

class PlayState : public GameState
{
public:
	PlayState(Vector2 &t_screenDimensions,GameStateMachine* t_stateMachine);
	virtual void update();
	virtual void render();
	virtual void processEvents(bool &isRunning);

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_playID; };


private:
	void cameraSetup();
	void collisions();
	void MenuInit();
	double GenerateRandomNumber(double min, double max);
	void enemyKilledMessageSort(std::string type);

	static const std::string m_playID;
	RenderSystem* m_rs;
	CollisionSystem* m_cs;
	BehaviourTreeSystem* m_bts;

	//Player m_player;
	std::unique_ptr<IPlayer> m_playerBot;
	HUD* m_hud;

	SDL_Rect* camera;
	SDL_Rect* m_miniMap;
	SDL_Rect* level;
	SDL_Texture* m_miniMapTexture;

	//Ai* m_enemy = new Ai;
	//std::unique_ptr<IEnemy> enemy = FactoryEnemy::createEnemy(FactoryEnemy::ENEMY_HARD);
	std::vector<std::unique_ptr<IEnemy>> m_enemies;

	std::vector<std::unique_ptr<IEnemy>> m_btEnemy;

	std::vector<PickUp*> m_pickUp;
	Map* myMap;

	Vector2 m_cameraDimensions;

	GameStateMachine* m_stateMachine;


	Audio* m_background;

	// Pause Menu Parts
	bool m_menuActive;
	SDL_Rect* m_menuBackground;
	SDL_Texture* m_menuBackgroundTexture;

	SDL_Rect* m_playOption;
	SDL_Texture* m_playOptionTexture;

	SDL_Rect* m_exitOption;
	SDL_Texture* m_exitOptionTexture;

	TTF_Font* m_font;
	Text* m_text[2];
	std::string className;

	std::vector<Entity*> m_miniMapList;

	bool bossSpawned = false;
	GameData m_data;


	std::vector<PopUpText*> message;
	TTF_Font* Abel;

	int EndTimer = 0;
	int localLevelKillCount = 0;

	ParticleSystem* m_particleEffects;
	Vector2 bloodPos;
};

#endif