#ifndef FACTORYPLAYER
#define FACTORYPLAYER

#include <memory>
#include "IPlayer.h"
#include "Warrior.h"
#include "Mage.h"
#include "Knight.h"
class FactoryPlayer
{
public:
	enum PLAYER_TYPE { PLAYER_WARRIOR, PLAYER_MAGE, PLAYER_KNIGHT };

	FactoryPlayer();

	virtual ~FactoryPlayer();

	static std::unique_ptr<IPlayer> createPlayer(PLAYER_TYPE t_playerType);
};

#endif // !FACTORYPLAYER