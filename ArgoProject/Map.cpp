#include "Map.h"

Map::Map(RenderSystem* t_rs, CollisionSystem* t_cs)
{
	for (int i = 0; i < roomsNum; i++)
	{
		if (i == 0)
		{
			map.push_back(std::make_unique<Room>(7, 7, Vector2(0,0), t_rs, t_cs));
		}
		if (i == roomsNum - 1)
		{
			map.push_back(std::make_unique<Room>(11, 11, Vector2(45 * tileSize, 15 * tileSize), t_rs, t_cs));
		}
		else
		{
			map.push_back(std::make_unique<Room>(7, 7, Vector2((rand() % 33 + 4) * tileSize, (rand() % 33 + 5) * tileSize), t_rs, t_cs));
		}
	}

	for (int i = 0; i < map.size(); i++)
	{
		WayPoints.push_back(map[i]->getCenterPos());
	}
}

Map::~Map()
{
}

void Map::CreateMap(RenderSystem* t_rs, CollisionSystem* t_cs)
{
	int y = 0;

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map.size(); j++)
		{
			if (j != i)
			{
				map[j]->checkForOverlap(map[i]->tileList, t_rs, t_cs); // the list thats passed is the one that is being changed. and the one calling the function is the one tiles are being deleted from
			}
		}
	}

	for (int i = 0; i < map.size(); i++)
	{
		map[i]->deleteOverlaps(t_rs, t_cs);
	}


	for (int i = 1; i < map.size(); i++)
	{
		if (i != y)
		{
			CreatePath(map[y]->getCenterPos(), map[i]->getCenterPos(), "Path", t_rs, t_cs);
		}
		y++;
	}

	for (int i = 0; i < map.size(); i++)
	{
		for (int x = 0; x < map[i]->tileList.size(); x++)
		{
			mapInfo.push_back(map[i]->tileList[x]->getEntity());

		}
	}

	for (int i = 0; i < path.size(); i++)
	{
		mapInfo.push_back(path[i]->getEntity());

	}
}


void Map::CreatePath(Vector2 start, Vector2 end, std::string tag, RenderSystem* t_rs, CollisionSystem* t_cs)
{
	//Some Collisions Could be borken due to the path tiles not being added to lists this will cause the wall to not be deleted.
	// Fix wall Double up Issue?	
	Vector2 newStart = start;
	Vector2 newEnd = end;

	Vector2 direction = newEnd - newStart;

	bool createNew = false;
	bool createSideWalls = true;
	bool skipLeft = false;
	bool skipRight = false;
	bool skipUp = false;
	bool skipDown = false;

	for (int i = 0; i < map.size(); i++)
	{
		for (int k = 0; k < map[i]->tileList.size(); k++)
		{
			if (start == map[i]->tileList[k]->getPos())
			{
				if (map[i]->tileList[k]->getTag() == "Floor")
				{
					createNew = true;
					createSideWalls = false;
				}

				if (map[i]->tileList[k]->getTag() == "Wall")
				{
					createSideWalls = false;

					map[i]->tileList[k]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);
					t_rs->deleteEntity(map[i]->tileList[k]->getEntity());
					t_cs->deleteEntity(map[i]->tileList[k]->getEntity());
					map[i]->tileList[k] = nullptr;
					map[i]->tileList.erase(map[i]->tileList.begin() + k);
				}
			}
		}
	}

	for (int i = 0; i < path.size(); i++)
	{
		if (start == path[i]->getPos())
		{
			if (path[i]->getTag() == "Wall")
			{
				path[i]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);
				t_rs->deleteEntity(path[i]->getEntity());
				t_cs->deleteEntity(path[i]->getEntity());
				path[i] = nullptr;
				path.erase(path.begin() + i);
			}
		}
	}

	if (newStart.x != newEnd.x)
	{
		for (int i = 0; i < path.size(); i++)
		{
			if (start + Vector2(0, tileSize) == path[i]->getPos())
			{
				skipDown = true;
			}

			if (start + Vector2(0, -tileSize) == path[i]->getPos())
			{
				skipUp = true;
			}
		}
		if (direction.x <= 0)
		{
			if (createNew == false)
			{
				if (createSideWalls == true)
				{
					if (skipDown == false)
					{
						Tile* temp1 = new Tile(newStart + Vector2(0, tileSize), tileSize, tileSize, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp1);
						temp1 = nullptr;
					}
					if (skipUp == false)
					{
						Tile* temp2 = new Tile(newStart + Vector2(0, -tileSize), tileSize, tileSize, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp2);
						temp2 = nullptr;
					}
				}
				Tile* temp3 = new Tile(newStart, tileSize, tileSize, returnTileType("Floor"), "Path", t_rs, t_cs);
				path.push_back(temp3);
				temp3 = nullptr;

			}
			newStart.x -= tileSize;
		}
		if (direction.x >= 0)
		{
			if (createNew == false)
			{
				if (createSideWalls == true)
				{
					if (skipDown == false)
					{
						Tile* temp1 = new Tile(newStart + Vector2(0, tileSize), tileSize, tileSize, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp1);
						temp1 = nullptr;
					}
					if (skipUp == false)
					{
						Tile* temp2 = new Tile(newStart + Vector2(0, -tileSize), tileSize, tileSize, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp2);
						temp2 = nullptr;
					}
				}
				Tile* temp = new Tile(newStart, tileSize, tileSize, returnTileType("Floor"), "Path", t_rs, t_cs);
				path.push_back(temp);
				temp = nullptr;
			}
			newStart.x += tileSize;
		}
		CreatePath(newStart, newEnd, "Path", t_rs, t_cs);

	}
	if (newStart.y != newEnd.y && newStart.x == newEnd.x)
	{
		for (int i = 0; i < path.size(); i++)
		{
			if (start + Vector2(tileSize, 0) == path[i]->getPos())
			{
				skipRight = true;
			}

			if (start + Vector2(-tileSize, 0) == path[i]->getPos())
			{
				skipLeft = true;
			}
		}
		if (direction.y <= 0)
		{
			if (createNew == false)
			{
				if (createSideWalls == true)
				{
					if (skipRight == false)
					{
						Tile* temp1 = new Tile(newStart + Vector2(tileSize, 0), tileSize, tileSize, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp1);
						temp1 = nullptr;
					}

					if (skipLeft == false)
					{
						Tile* temp2 = new Tile(newStart + Vector2(-tileSize, 0), tileSize, tileSize, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp2);
						temp2 = nullptr;
					}
				}
				Tile* temp = new Tile(newStart, tileSize, tileSize, returnTileType("Floor"), "Path", t_rs, t_cs);
				path.push_back(temp);
				temp = nullptr;
			}
			newStart.y -= tileSize;
		}
		if (direction.y >= 0)
		{
			if (createNew == false)
			{
				if (createSideWalls == true)
				{
					if (skipRight == false)
					{
						Tile* temp1 = new Tile(newStart + Vector2(tileSize, 0), tileSize, tileSize, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp1);
						temp1 = nullptr;
					}

					if (skipLeft == false)
					{
						Tile* temp2 = new Tile(newStart + Vector2(-tileSize, 0), tileSize, tileSize, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp2);
						temp2 = nullptr;
					}
				}
				Tile* temp = new Tile(newStart, tileSize, tileSize, returnTileType("Floor"), "Path", t_rs, t_cs);
				path.push_back(temp);
				temp = nullptr;
			}
			newStart.y += tileSize;
		}
		CreatePath(newStart, newEnd, "Path", t_rs, t_cs);
	}
}


std::string Map::returnTileType(std::string type)
{
	int tileNum;
	std::string tileName;
	if (type == "Wall")
	{
		tileNum = rand() % 5;
		switch (tileNum)
		{
		case 0:
			tileName = "Assets/tiles/WALL1.png";
			return tileName;
			break;
		case 1:
			tileName = "Assets/tiles/WALL2.png";
			return tileName;
			break;
		case 2:
			tileName = "Assets/tiles/WALL3.png";
			return tileName;
			break;
		case 3:
			tileName = "Assets/tiles/WALL4.png";
			return tileName;
			break;
		case 4:
			tileName = "Assets/tiles/WALL5.png";
			return tileName;
			break;
		default:
			tileName = "Assets/tiles/WALL5.png";
			return tileName;
			break;
		}

	}
	
	if (type == "Floor")
	{
		tileNum = rand() % 12 + 1;
		switch (tileNum)
		{
		case 1:
			tileName = "Assets/tiles/TILE1.png";
			return tileName;
			break;
		case 2:
			tileName = "Assets/tiles/TILE2.png";
			return tileName;
			break;
		case 3:
			tileName = "Assets/tiles/TILE3.png";
			return tileName;
			break;
		case 4:
			tileName = "Assets/tiles/TILE4.png";
			return tileName;
			break;
		case 5:
			tileName = "Assets/tiles/TILE5.png";
			return tileName;
			break;
		case 6:
			tileName = "Assets/tiles/TILE6.png";
			return tileName;
			break;
		case 7:
			tileName = "Assets/tiles/TILE7.png";
			return tileName;
			break;
		case 8:
			tileName = "Assets/tiles/TILE8.png";
			return tileName;
			break;
		case 9:
			tileName = "Assets/tiles/TILE9.png";
			return tileName;
			break;
		case 10:
			tileName = "Assets/tiles/TILE10.png";
			return tileName;
			break;
		case 11:
			tileName = "Assets/tiles/TILE11.png";
			return tileName;
			break;
		case 12:
			tileName = "Assets/tiles/TILE12.png";
			return tileName;
			break;
		default:
			tileName = "Assets/tiles/TILE1.png";
			return tileName;
			break;
		}
	}

}

void Map::createHostMap(Vector2 pos, int id, RenderSystem* t_rs, CollisionSystem* t_cs)
{
	if (id == 0)
	{
		hostMap.push_back(std::make_unique<Tile>(pos, tileSize, tileSize, returnTileType("Wall"), "Wall", t_rs, t_cs));
	}
	if(id == -1)
	{
		hostMap.push_back(std::make_unique<Tile>(pos, tileSize, tileSize, returnTileType("Floor"), "Floor", t_rs, t_cs));
	}

	if (id != -1 || id != 0)
	{
		return;
	}
}

