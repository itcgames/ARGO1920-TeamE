#include "Map.h"

Map::Map(RenderSystem* t_rs, CollisionSystem* t_cs)
{
	for (int i = 0; i < roomsNum; i++)
	{
		map.push_back(std::make_unique<Room>(7,7, Vector2((rand() % 33 + 0) * 100, (rand() % 30 + 0) * 100), t_rs, t_cs));
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
}


void Map::CreatePath(Vector2 start, Vector2 end, std::string tag, RenderSystem* t_rs, CollisionSystem* t_cs)
{
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

					if (map[i]->tileList[k]->getTag() == "Wall")
					{
						t_cs->deleteEntity(map[i]->tileList[k]->getEntity());
					}


					map[i]->tileList[k] = nullptr;
					map[i]->tileList.erase(map[i]->tileList.begin() + k);
				}
			}
		}
	}
	
	if (newStart.x != newEnd.x)
	{
		for (int i = 0; i < path.size(); i++)
		{
			if (start + Vector2(0, 100) == path[i]->getPos())
			{
				skipDown = true;
			}

			if (start + Vector2(0, -100) == path[i]->getPos())
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
						Tile* temp1 = new Tile(newStart + Vector2(0, 100), 100, 100, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp1);
						temp1 = nullptr;
					}
					if (skipUp == false)
					{
						Tile* temp2 = new Tile(newStart + Vector2(0, -100), 100, 100, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp2);
						temp2 = nullptr;
					}
				}
				Tile* temp3 = new Tile(newStart, 100, 100, returnTileType("Floor"), "Path", t_rs, t_cs);
				path.push_back(temp3);
				temp3 = nullptr;

			}
			newStart.x -= 100;
		}
		if (direction.x >= 0)
		{
			if (createNew == false)
			{
				if (createSideWalls == true)
				{
					if (skipDown == false)
					{
						Tile* temp1 = new Tile(newStart + Vector2(0, 100), 100, 100, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp1);
						temp1 = nullptr;
					}
					if (skipUp == false)
					{
						Tile* temp2 = new Tile(newStart + Vector2(0, -100), 100, 100, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp2);
						temp2 = nullptr;
					}
				}
				Tile* temp = new Tile(newStart, 100, 100, returnTileType("Floor"), "Path", t_rs, t_cs);
				path.push_back(temp);
				temp = nullptr;
			}
			newStart.x += 100;
		}
		CreatePath(newStart, newEnd,"Path", t_rs, t_cs);

	}
	if (newStart.y != newEnd.y && newStart.x == newEnd.x)
	{
		for (int i = 0; i < path.size(); i++)
		{
			if (start + Vector2(100, 0) == path[i]->getPos())
			{
				skipRight = true;
			}

			if (start + Vector2(-100, 0) == path[i]->getPos())
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
						Tile* temp1 = new Tile(newStart + Vector2(100, 0), 100, 100, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp1);
						temp1 = nullptr;
					}

					if (skipLeft == false)
					{
						Tile* temp2 = new Tile(newStart + Vector2(-100, 0), 100, 100, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp2);
						temp2 = nullptr;
					}
				}
				Tile* temp = new Tile(newStart, 100, 100, returnTileType("Floor"), "Path", t_rs, t_cs);
				path.push_back(temp);
				temp = nullptr;
			}
			newStart.y -= 100;
		}
		if (direction.y >= 0)
		{
			if (createNew == false)
			{
				if (createSideWalls == true)
				{
					if (skipRight == false)
					{
						Tile* temp1 = new Tile(newStart + Vector2(100, 0), 100, 100, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp1);
						temp1 = nullptr;
					}

					if (skipLeft == false)
					{
						Tile* temp2 = new Tile(newStart + Vector2(-100, 0), 100, 100, returnTileType("Wall"), "Wall", t_rs, t_cs);
						path.push_back(temp2);
						temp2 = nullptr;
					}
				}
				Tile* temp = new Tile(newStart, 100, 100, returnTileType("Floor"), "Path", t_rs, t_cs);
				path.push_back(temp);
				temp = nullptr;
			}
			newStart.y += 100;
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

