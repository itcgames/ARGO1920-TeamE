#ifndef ROOM
#define ROOM
//#pragma once
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
	Room(int sizeX, int sizeY, Vector2 pos,RenderSystem* t_rs, CollisionSystem* t_cs);
	~Room();

	void checkForOverlap(std::vector<std::unique_ptr<Tile>>& t, RenderSystem* t_rs, CollisionSystem* t_cs);
	void deleteOverlaps(RenderSystem* t_rs, CollisionSystem* t_cs);

	Vector2 getCenterPos();
	Vector2 getSize();
	int getWallsCount();
	int getFloorCount();

	std::string returnTileType(std::string type);

	int m_tileSize = 300;

	int roomSizeX;
	int roomSizeY;

	int wallCount = 0;
	int floorCount = 0;
	int doorCount = 0;

	Vector2 m_roomPos;

	std::vector<std::unique_ptr<Tile>> tileList;

	bool collided = false;
	bool roomChecked = false;
};

#endif