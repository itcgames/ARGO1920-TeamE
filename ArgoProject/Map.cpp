#include "Map.h"

Map::Map(RenderSystem* t_rs, CollisionSystem* t_cs)
{
	for (int i = 0; i < roomsNum; i++)
	{
		map.push_back(std::make_unique<Room>(rand() % 7 + 5, rand() % 7 + 5, Vector2((rand() % 33 + 0) * 100, (rand() % 30 + 0) * 100), t_rs, t_cs));
	}
}

Map::~Map()
{
}

void Map::CreateMap(RenderSystem* t_rs, CollisionSystem* t_cs)
{
	int y = 0;

	for (int i = 1; i < map.size(); i++)
	{
		CreatePath(map[y]->getCenterPos(), map[i]->getCenterPos(),"Path", t_rs, t_cs);
		y++;
	}

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map.size(); j++)
		{
			map[j]->checkForOverlap(map[i]->tileList,t_rs,t_cs); // the list thats passed is the one that is being changed. and the one calling the function is the one tiles are being deleted from
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



void Map::CreatePath(Vector2 start, Vector2 end, std::string tag, RenderSystem* t_rs, CollisionSystem* t_cs)
{
	Vector2 newStart = start;
	Vector2 newEnd = end;

	Vector2 direction = newEnd - newStart;

	bool createNew = false;
	for (int i = 0; i < map.size(); i++)
	{
		for (int k = 0; k < map[i]->tileList.size(); k++)
		{
			if (start == map[i]->tileList[k]->getPos())
			{
				if (map[i]->tileList[k]->getTag() == "Wall")
				{
					delete map[i]->tileList[k].release();
					map[i]->tileList[k] = nullptr;
					map[i]->tileList.erase(map[i]->tileList.begin() + k);
				}
			}
		}
	}
	if (newStart.x != newEnd.x)
	{
		if (direction.x <= 0)
		{
			if (createNew == false)
			{
				Tile* temp = new Tile(newStart, 100, 100, "Assets/Tiles/TILE1.png", "Path", t_rs, t_cs);
				path.push_back(temp);
				temp = nullptr;
			}
			newStart.x -= 100;
		}
		if (direction.x >= 0)
		{
			if (createNew == false)
			{
				Tile* temp = new Tile(newStart, 100, 100, "Assets/Tiles/TILE1.png", "Path", t_rs, t_cs);
				path.push_back(temp);
				temp = nullptr;
			}
			newStart.x += 100;
		}
		CreatePath(newStart, newEnd,"Path", t_rs, t_cs);

	}
	if (newStart.y != newEnd.y && newStart.x == newEnd.x)
	{
		if (direction.y <= 0)
		{
			if (createNew == false)
			{
				Tile* temp = new Tile(newStart, 100, 100, "Assets/Tiles/TILE1.png", "Path", t_rs, t_cs);
				path.push_back(temp);
				temp = nullptr;
			}
			newStart.y -= 100;
		}
		if (direction.y >= 0)
		{
			if (createNew == false)
			{
				Tile* temp = new Tile(newStart, 100, 100, "Assets/Tiles/TILE1.png", "Path", t_rs, t_cs);
				path.push_back(temp);
				temp = nullptr;
			}
			newStart.y += 100;
		}
		CreatePath(newStart, newEnd, "Path", t_rs, t_cs);
	}
}

