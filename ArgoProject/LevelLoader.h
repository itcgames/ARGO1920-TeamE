 #ifndef LEVELLOADER
#define LEVELLOADER

#include "yaml-cpp\yaml.h"
#include "SDL.h"
#include "Vector2.h"
#include <iostream>
#include <vector>
#include <fstream>



struct HighScoreData
{
	std::string m_name;
	float m_score;
};

struct GroundData
{
	Vector2 m_position;
};

struct LevelData
{
	std::vector<GroundData> m_groundPoints;
};

/// <summary>
/// @bried Struct to load level data
/// </summary>
struct GameData 
{
	std::vector<HighScoreData> m_scores;//done

	LevelData m_level1;
	LevelData m_level2;
	LevelData m_level3;
};

class LevelLoader
{
private:
	static YAML::Node m_baseNode;
public:
	LevelLoader() = default;

	//load function to be passed a number for a level along 
	//with the level data
	static bool load(int t_nr, GameData & t_level);

	//load function passed the name of the file to be opened
	static bool load(std::string t_fileName,GameData & t_level);

	static void write(std::string t_playerName[], int t_playerScore[]);

	static void writeNode(const YAML::Node& node, YAML::Emitter& emitter);
	
};


#endif // !LEVELLOADER

