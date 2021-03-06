#ifndef MULTIPLAYERSTATE
#define MULTIPLAYERSTATE
#include "ParticleSystem.h"
#include "GameState.h"
#include "EndState.h"
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

class MultiplayerState : public GameState
{
public:
	MultiplayerState(Vector2& t_screenDimensions, GameStateMachine* t_stateMachine);
	virtual void update();
	virtual void render();
	virtual void processEvents(bool& isRunning);

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_playID; };


private:
	void cameraSetup();
	void collisions();
	void MenuInit();
	double GenerateRandomNumber(double min, double max);
	void ParseMapData();


	static const std::string m_playID;
	RenderSystem* m_rs;
	CollisionSystem* m_cs;
	BehaviourTreeSystem* m_bts;

	//Player m_player;
	std::unique_ptr<IPlayer> m_player;
	std::unique_ptr<IPlayer> m_player2;
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

	Server m_server{ 8888, true };
	//Client m_client{ data::Instance()->IPADDRESS, 1111 };
	Client m_client{ "149.153.106.175", 8888 }; // Connect to Aoife


	Audio m_background;

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
	bool mapMade = false;
	std::string sendMap;

	std::string mapDataRecString;
	std::vector<float> m_mapX;
	std::vector<float> m_mapY;
	std::vector<int> m_mapTileID;
};

#endif
