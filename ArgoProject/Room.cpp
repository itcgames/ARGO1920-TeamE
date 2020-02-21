#include "Room.h"

Room::Room(int sizeX, int sizeY, Vector2 pos, RenderSystem* t_rs, CollisionSystem* t_cs)
{
	m_roomPos = pos;

	roomSizeX = sizeX;
	roomSizeY = sizeY;

	for (int i = 0; i < roomSizeX; i++)
	{
		for (int z = 0; z < roomSizeY; z++)
		{
			// Checks for the edges of the room
			if(i == 0 || i == roomSizeX -1 || z == 0 || z == roomSizeY -1)
			{ 
				tileList.push_back(std::make_unique<Tile>(Vector2(m_roomPos.x + (i * m_tileSize), m_roomPos.y + (z * m_tileSize)), m_tileSize, m_tileSize,/*"Assets/Tiles/tile.png"*/ returnTileType("Wall"), "Wall", t_rs, t_cs));
				wallCount++;
			}
			else
			{
				tileList.push_back(std::make_unique<Tile>(Vector2(m_roomPos.x + (i * m_tileSize), m_roomPos.y + (z * m_tileSize)), m_tileSize, m_tileSize, returnTileType("Floor"), "Floor", t_rs, t_cs));
				floorCount++;
			}
		}
	}
}

Room::~Room()
{
}


void Room::checkForOverlap(std::vector<std::unique_ptr<Tile>>& t, RenderSystem* t_rs, CollisionSystem* t_cs)
{

	// T is the other room you are hitting ( its rendered above you )
	for (int i = 0; i < tileList.size(); i++)
	{
		for (int y = 0; y < t.size(); y++)
		{
			if (tileList[i]->getPos() == t[y]->getPos()) // checks the positions are the same
			{

				if (tileList[i]->getTag() != t[y]->getTag()) // checks that the tags are the same 
				{
					if (tileList[i]->getTag() == "Wall")
					{
						//tileList[i]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);
						//t_rs->deleteEntity(tileList[i]->getEntity());
						//t_cs->deleteEntity(tileList[i]->getEntity());

						//tileList[i] = nullptr;
						//tileList.erase(tileList.begin() + i);
						//tileList[i] = std::move(std::unique_ptr<Tile>(new Tile(tileList[i]->getPos(), 50, 50, "Assets/tiles/tile.png", "Floor", t_rs, t_cs))); // replaces the tile
					}

					if (t[y]->getTag() == "Wall")
					{
						t[y]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);
						t_rs->deleteEntity(t[y]->getEntity());
						t_cs->deleteEntity(t[y]->getEntity());

						t[y] = nullptr;
						t.erase(t.begin() + y);
					}
				}
			}
		}
	}
}

void Room::pathOverlaping(RenderSystem* t_rs, CollisionSystem* t_cs)
{
}


Vector2 Room::getCenterPos()
{
		return Vector2(tileList[(roomSizeX * roomSizeY) / 2]->getPos());
}

Vector2 Room::getSize()
{
	return Vector2(roomSizeX,roomSizeY);
}

int Room::getWallsCount()
{
	return wallCount;
}

int Room::getFloorCount()
{
	return floorCount;
}

std::string Room::returnTileType(std::string type)
{
	int tileNum;
	std::string tileName;
	if (type == "Wall")
	{
		tileNum = rand() % 5 + 1;
		switch (tileNum)
		{
		case 1:
			tileName = "Assets/tiles/WALL1.png";
			return tileName;
			break;
		case 2:
			tileName = "Assets/tiles/WALL2.png";
			return tileName;
			break;
		case 3:
			tileName = "Assets/tiles/WALL3.png";
			return tileName;
			break;
		case 4:
			tileName = "Assets/tiles/WALL4.png";
			return tileName;
			break;
		case 5:
			tileName = "Assets/tiles/WALL5.png";
			return tileName;
			break;
		default:
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
			break;
		}
	}

}
