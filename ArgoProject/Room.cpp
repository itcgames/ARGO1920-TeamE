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
				tileList.push_back(std::make_unique<Tile>(Vector2(m_roomPos.x + (i * m_tileSize), m_roomPos.y + (z * m_tileSize)), m_tileSize, m_tileSize, "Assets/tiles/tileTwo.png", "Wall", t_rs, t_cs));
				wallCount++;
			}
			else
			{
				tileList.push_back(std::make_unique<Tile>(Vector2(m_roomPos.x + (i * m_tileSize), m_roomPos.y + (z * m_tileSize)), m_tileSize, m_tileSize, "Assets/tiles/TILE1.png", "Floor", t_rs, t_cs));
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
				if (t[y] != nullptr) // checks that its not empty 
				{
					if (tileList[i]->getPos() == t[y]->getPos()) // checks the positions are the same
					{
						if (tileList[i]->getTag() != t[y]->getTag()) // checks that the tags are the same 
						{
							t[y]->covered = true;
						}

						if (tileList[i]->getTag() == "Floor" && t[y]->getTag()== "Floor") // checks that the tags are the same 
						{
							t[y]->covered = true;
						}
					}
				}
		}
	}

	////For loop for deleting
	//for (int i = 0; i < tileList.size(); i++)
	//{
	//	if (tileList[i]->covered == true)
	//	{
	//		if (tileList[i]->getTag() == "Wall")
	//		{
	//			wallCount--;
	//		}
	//		if (tileList[i]->getTag() == "Floor")
	//		{
	//			floorCount--;
	//		}

	//		tileList[i]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);
	//		t_rs->deleteEntity(tileList[i]->getEntity());

	//		if (tileList[i]->getTag() == "Wall")
	//		{
	//			t_cs->deleteEntity(tileList[i]->getEntity());
	//		}

	//		//delete tileList[i].release();
	//		if (tileList[i]->getTag() == "Floor")
	//		{
	//			tileList[i] = std::move(std::unique_ptr<Tile>(new Tile(tileList[i]->getPos(), m_tileSize, m_tileSize, "Assets/tiles/TILE1.png", "Floor", t_rs, t_cs))); // replaces the tile
	//		}
	//		else
	//		{
	//			tileList[i] = nullptr;
	//			tileList.erase(tileList.begin() + i);
	//		}
	//	}
	//}
	//std::cout << t_rs->getEntitiesSize() << std::endl;

}

void Room::deleteOverlaps(RenderSystem* t_rs, CollisionSystem* t_cs)
{
	//For loop for deleting
	for (int i = 0; i < tileList.size(); i++)
	{
		if (tileList[i]->covered == true)
		{
			if (tileList[i]->getTag() == "Wall")
			{
				wallCount--;
			}
			if (tileList[i]->getTag() == "Floor")
			{
				floorCount--;
			}

			tileList[i]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);
			t_rs->deleteEntity(tileList[i]->getEntity());

			if (tileList[i]->getTag() == "Wall")
			{
				t_cs->deleteEntity(tileList[i]->getEntity());
			}

			//delete tileList[i].release();
			if (tileList[i]->getTag() == "Floor")
			{
				tileList[i] = std::move(std::unique_ptr<Tile>(new Tile(tileList[i]->getPos(), m_tileSize, m_tileSize, "Assets/tiles/TILE1.png", "Floor", t_rs, t_cs))); // replaces the tile
			}
			else
			{
				tileList[i] = nullptr;
				tileList.erase(tileList.begin() + i);
			}
		}
	}
	std::cout << t_rs->getEntitiesSize() << std::endl;
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
