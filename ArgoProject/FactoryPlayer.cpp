#include "FactoryPlayer.h"

FactoryPlayer::FactoryPlayer()
{
}

FactoryPlayer::~FactoryPlayer()
{
}

std::unique_ptr<IPlayer> FactoryPlayer::createPlayer(PLAYER_TYPE t_playerType)
{
	switch (t_playerType)
	{
	case PLAYER_WARRIOR:
		return std::make_unique<Warrior>();
	case PLAYER_MAGE:
		return std::make_unique<Mage>();
	case PLAYER_KNIGHT:
		return std::make_unique<Knight>();
	default:
		return std::make_unique<Warrior>();
	}
	return std::unique_ptr<IPlayer>();
}
