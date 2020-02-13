//
// C00204076
// Brandon Seah-Dempsey
// Started at 10:10 12 Feburary 2020
// Finished
// Time taken:
// Known bugs:

#ifndef PICKUP_H
#define PICKUP_H

#include "ECS.h"
#include "SDL.h"
#include "Entity.h"
#include "RenderSystem.h"
#include "BehaviourSystem.h"
#include "Renderer.h"
#include "Data.h"

class PickUp
{
public:
	void initialize(RenderSystem* t_rs, std::string type, bool isSmall, bool isMedium, bool isLarge);
	void update();
	void destroy();

	Entity* getEntity();
	SDL_Rect* getRect();

private:
	Entity* m_item;
	SDL_Rect* m_rect;
	SDL_Texture* m_texture;
	PositionComponent* m_pc;
	SpriteComponent* m_sc;
	ItemComponent* m_ic;
};

#endif // !PICKUP_H

