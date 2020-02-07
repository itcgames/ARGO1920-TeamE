#include "Room.h"

Room::Room(int sizeX, int sizeY, Vector2 pos, RenderSystem* t_rs)
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
				Tile* temp = new Tile(Vector2(m_roomPos.x + (i * m_tileSize), m_roomPos.y + (z * m_tileSize)), m_tileSize, m_tileSize, "Assets/tileTwo.png", "Wall",t_rs);
				tileList.push_back(temp);
				wallCount++;
			}
			else
			{
				Tile* temp = new Tile(Vector2(m_roomPos.x + (i * m_tileSize), m_roomPos.y + (z * m_tileSize)), m_tileSize, m_tileSize, "Assets/tile.png", "Floor", t_rs);
				tileList.push_back(temp);
				floorCount++;
			}
		}
	}
}

Room::~Room()
{
}


void Room::render()
{
	//for (int i = 0; i < tileList.size(); i++)
	//{
	//	if (tileList.at(i) != nullptr)
	//	{
	//		tileList.at(i)->render();
	//	}
	//}
}

void Room::update()
{
}

void Room::checkForOverlap(std::vector<Tile*>& t, RenderSystem* t_rs)
{
	// T is the other room you are hitting ( its rendered above you )
	for (int i = 0; i < tileList.size(); i++)
	{
		for (int y = 0; y < t.size(); y++)
		{
			if (t.at(y) != nullptr) // checks that its not empty 
			{
				if (tileList.at(i)->getPos() == t.at(y)->getPos()) // checks the positions are the same
				{
					if (tileList.at(i)->getTag() != t.at(y)->getTag()) // checks that the tags are the same 
					{
						tileList.at(i)->covered = true; // set a bool that deletes them if its true
						t.at(y) = new Tile(t.at(y)->getPos(), m_tileSize, m_tileSize, "Assets/tile.png", "Floor", t_rs); // replaces the tile
						collided = true; // checks that this room has collided with another
					}
				}

			}
		}
	}


	//For loop for deleting
	for (int i = 0; i < tileList.size(); i++)
	{
		if (tileList.at(i)->covered == true)
		{
			if (tileList.at(i)->getTag() == "Wall")
			{
				wallCount--;
			}
			if (tileList.at(i)->getTag() == "Floor")
			{
				floorCount--;
			}

			delete tileList.at(i);
			tileList.at(i) = nullptr;
			tileList.erase(tileList.begin() + i);
		}
	}
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
