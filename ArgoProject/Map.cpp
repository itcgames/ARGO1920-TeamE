#include "Map.h"

Map::Map(RenderSystem* t_rs, CollisionSystem* t_cs)
{
	for (int i = 0; i < roomsNum; i++)
	{
		map.push_back(std::make_unique<Room>(rand() % 7 + 5, rand() % 7 + 5, Vector2((rand() % 33 + 0) * 50, (rand() % 30 + 0) * 50), t_rs, t_cs));
	}
}

Map::~Map()
{
}

void Map::CreateMap(RenderSystem* t_rs, CollisionSystem* t_cs)
{

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map.size(); j++)
		{
			map.at(j)->checkForOverlap(map[i]->tileList,t_rs,t_cs); // the list thats passed is the one that is being changed. and the one calling the function is the one tiles are being deleted from
		}
	}

	//Works for just two
	//if (map.at(0).collided == true)
	//{
	//	map.at(0).tileList.insert(map.at(0).tileList.end(), map.at(1).tileList.begin(), map.at(1).tileList.end());		
	//	map.at(1).tileList.clear();
	//}

	//if (map.at(1).collided == true)
	//{
	//	map.at(1).tileList.insert(map.at(1).tileList.end(), map.at(0).tileList.begin(), map.at(0).tileList.end());
	//	map.at(0).tileList.clear();
	//}

}



void Map::CreatePath(Vector2 start, Vector2 end)
{

}

