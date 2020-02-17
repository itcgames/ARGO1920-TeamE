#ifndef TILE
#define TILE
//#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2.h"
#include "Renderer.h"
#include "Entity.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"
#include <iostream>
class Tile
{
public:
	Tile(Vector2 pos, int width, int height, std::string path,std::string tileTag, RenderSystem* t_rs, CollisionSystem* t_cs);
	~Tile();

	void render();
	Vector2 getPos();
	int getHeight();
	int getWidth();
	std::string getTag();
	Entity* getEntity() { return m_tile; };


	bool covered = false;


	Entity* m_tile;
	PositionComponent* m_pc;
	SpriteComponent* m_sc;


	Vector2 m_position = { 0,0 };

	int WIDTH=0;
	int HEIGHT=0;
	
	SDL_Texture* img = NULL;
	SDL_Rect* endRect;

	std::string tag = "";

};

#endif