#pragma once
#include<iostream>
#include "LevelLoader.h"
class Data
{
public:
	static Data* Instance()
	{
		if (m_Instance == 0)
		{
			m_Instance = new Data();
			return m_Instance;
		}

		return m_Instance;
	}

	void setUpData(GameData& t_data) { m_data = t_data; }

	GameData& getData() { return m_data; }
private:
	static Data* m_Instance;
	GameData m_data;
};

typedef Data data;