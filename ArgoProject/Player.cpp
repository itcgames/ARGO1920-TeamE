#include "Player.h"

void Player::init(RenderSystem* t_rs, SDL_Rect* t_camera, Vector2 startPos)
{
	//creates a soucre and size rectangle for the player animation
	m_playerRect = new SDL_Rect();
	playerPos = new SDL_Rect();
	m_playerRect->x = startPos.x; m_playerRect->y = startPos.y;
	playerPos->x = 0; playerPos->y = 0;

	//load in the player texture
	SDL_Surface* playerSurface = IMG_Load("Assets/placeholderanim.png");
	m_playerTexture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), playerSurface);
	SDL_QueryTexture(m_playerTexture, NULL, NULL, &textureWidth, &textureHeight);

	//set both rectangles to the size of one frame from the sprite sheet
	frameWidth = textureWidth / 8;
	frameHeight = textureHeight;
	m_playerRect->w = frameWidth /2; m_playerRect->h = frameHeight /2;
	playerPos->w = frameWidth /2; playerPos->h = frameHeight /2;

	m_player = new Entity();
	m_bs = new BehaviourSystem;
	finiteStateMachine = new FSM();
	state = new FiniteState();

	m_pc = new PositionComponent(Vector2(m_playerRect->x, m_playerRect->y), 1);
	m_sc = new SpriteComponent(m_playerTexture, m_playerRect, 2);
	m_bc = new BehaviourComponent(Vector2(0, 0), 10, 0, 3);
	m_statc = new StatsComponent(data::Instance()->getData().m_playerStats.at(0).m_class, data::Instance()->getData().m_playerStats.at(0).m_health,
		data::Instance()->getData().m_playerStats.at(0).m_strength, data::Instance()->getData().m_playerStats.at(0).m_speed,
		data::Instance()->getData().m_playerStats.at(0).m_gold, data::Instance()->getData().m_playerStats.at(0).m_killCount, 4);
	m_ac = new ActiveComponent(true);

	m_player->setID(1);
	m_player->addComponent<PositionComponent>(m_pc, 1);
	m_player->addComponent<SpriteComponent>(m_sc, 2);
	m_player->addComponent<BehaviourComponent>(m_bc, 3);
	m_player->addComponent<StatsComponent>(m_statc, 4);
	m_player->addComponent<ActiveComponent>(m_ac, 6);
	
	m_rs = t_rs;
	m_bs->addEntity(m_player);
	t_rs->addEntity(m_player);

	m_camera = t_camera;

	//Input InputHandler
	m_ih = new InputHandler();
	m_ih->addEntity(m_player);

	m_ih->mousePosition = startPos;
}

void Player::update()
{
	//checks if the player is in walking state
	if (finiteStateMachine->getCurrentState() == 1)
	{
		//the player seeks the mouse position
		if (m_pc->getPosition().x != m_ih->mousePosition.x && m_pc->getPosition().y != m_ih->mousePosition.y)
		{
			//This is to stop the jittering in the movement.         
			float mag = sqrt((m_pc->getPosition().x - m_ih->mousePosition.x) * (m_pc->getPosition().x - m_ih->mousePosition.x) + (m_pc->getPosition().y - m_ih->mousePosition.y) * (m_pc->getPosition().y - m_ih->mousePosition.y));
			if (mag > 40) 
			{            
				m_bs->seek(m_ih->mousePosition);
			}
			m_playerRect->x = m_pc->getPosition().x;
			m_playerRect->y = m_pc->getPosition().y;
		}
	}

	animate();

	if (m_ih->move)
	{
		finiteStateMachine->walking();
	}

	if (commandQueue.empty() && !m_ih->move)
	{
		finiteStateMachine->idle();
	}
	else while (!commandQueue.empty())
	{
		commandQueue.back()->execute(finiteStateMachine);
		commandQueue.pop_back();
	}
}

//generates the inputs and places them in the queue
void Player::processEvents(bool isRunning)
{
	m_ih->generateInputs(commandQueue, m_camera);
}

//animate the player sprite
void Player::animate()
{
	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 100) % 8;
	playerPos->x = sprite * (frameWidth /2);

	m_sc->setRect(playerPos);
	m_sc->setDstRect(m_playerRect);
}

