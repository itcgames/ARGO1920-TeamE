#ifndef PLAYSTATE
#define PLAYSTATE
#include "ParticleSystem.h"
#include "GameState.h"
#include "EndState.h"
#include "SDL.h"
#include "Data.h"
#include "Pickup.h"
#include "CollisionSystem.h"
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
	static const std::string m_playID;
	RenderSystem* m_rs;
	CollisionSystem* m_cs;
	//Player m_player;
	std::unique_ptr<IPlayer> m_player;
	HUD* m_hud;

	SDL_Rect* camera;
	SDL_Rect* m_miniMap;
	SDL_Rect* level;
	SDL_Texture* m_miniMapTexture;

	//Ai* m_enemy = new Ai;
	//std::unique_ptr<IEnemy> enemy = FactoryEnemy::createEnemy(FactoryEnemy::ENEMY_HARD);
	std::vector<std::unique_ptr<IEnemy>> m_enemies;
	PickUp* m_pickUp = new PickUp;
	Map* myMap;

	Vector2 m_cameraDimensions;

	GameStateMachine* m_stateMachine;

	Server m_server{ 1111, true };
	//Client m_client{ data::Instance()->IPADDRESS, 1111 };

	Client m_client{ "149.153.106.176", 1111 }; // Connect to Aoife

	Audio m_background;

	ParticleSystem* m_pSystem;
};

#endif