#ifndef MAP
#define MAP
//#pragma once
#include "Room.h"

#include "SDL.h"
#include "SDL_image.h"
#include "Vector2.h"
#include "Renderer.h"
#include <iostream>
#include <vector>
class Map
{
public:

	Map(RenderSystem* t_rs, CollisionSystem* t_cs);
	~Map();

	void CreateMap(RenderSystem* t_rs, CollisionSystem* t_cs);
	void CreatePath(Vector2 start, Vector2 end,std::string tag,RenderSystem* t_rs, CollisionSystem* t_cs);
	std::string returnTileType(std::string type);

	void createHostMap(Vector2 pos, int id, RenderSystem* t_rs, CollisionSystem* t_cs);


	std::vector<std::unique_ptr<Room>> map;
	std::vector < std::unique_ptr<Tile>> hostMap;
	std::vector<Tile*> path;

	int roomsNum = 20;
	int tileSize = 300;

	std::vector<Entity*> mapInfo;

};

#endif