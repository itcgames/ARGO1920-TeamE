#include "Data.h"
Data* Data::m_Instance = 0;

void Data::setUpData(GameData& t_data)
{
	m_data = t_data;
	for (int i = 0; i < 10; i++)
	{
		oldNames[i] = m_data.m_scores.at(i).m_name;
		oldScores[i] = m_data.m_scores.at(i).m_score;
	}
}

void Data::newScore()
{
	int lowest = oldScores[0];
	int lowestIndex = 0;
	for (int i = 1; i < 10; i++)
	{
		if (oldScores[i] < lowest)
		{
			lowest = oldScores[i];
			lowestIndex = i;
		}
	}
	oldScores[lowestIndex] = playerScore;
	oldNames[lowestIndex] = playerName;

	writeNewScores();
}

void Data::writeNewScores()
{
	long int temp = 0;
	std::string nameTemp = "";
	for (int i = 0; i < 10; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (oldScores[j] > oldScores[i])
			{
				temp = oldScores[i];
				nameTemp = oldNames[i];
				oldScores[i] = oldScores[j];
				oldScores[j] = temp;
				oldScores[j] = temp;
				oldNames[j] = nameTemp;
			}
		}
		oldNames[i] = oldNames[i];
		LevelLoader::write(oldNames, oldScores);
	}
}
