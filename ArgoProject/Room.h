#pragma once
#include "Tile.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2.h"
#include "Renderer.h"
#include <iostream>
#include <vector>
#include "Entity.h"

class Room
{
public:
	Room(int sizeX, int sizeY, Vector2 pos,RenderSystem* t_rs);
	~Room();
	void render();
	void update();

	void checkForOverlap(std::vector<Tile*>& t, RenderSystem* t_rs);


	Vector2 getCenterPos();
	Vector2 getSize();
	int getWallsCount();
	int getFloorCount();

	int m_tileSize = 50;

	int roomSizeX;
	int roomSizeY;

	int wallCount = 0;
	int floorCount = 0;
	int doorCount = 0;

	Vector2 m_roomPos;

	std::vector<Tile*> tileList;

	bool collided = false;
	bool roomChecked = false;
};

