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

struct StatsData
{
	std::string m_class;
	int m_health;
	int m_strength;
	int m_speed;
	int m_gold;
	int m_killCount;
};

struct PlayerStatsData
{
	std::string m_class;
	int m_health;
	int m_strength;
	int m_speed;
	int m_gold;
	int m_killCount;
};

struct LevelData
{
	std::vector<StatsData> m_stats;
};

/// <summary>
/// @bried Struct to load level data
/// </summary>
struct GameData 
{
	std::vector<HighScoreData> m_scores; //done
	std::vector <PlayerStatsData> m_playerStats;
	LevelData m_presets;
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
	static void writeToPlayer(std::string t_class, int t_health, int t_strength, int t_speed, int t_gold, int t_killCount);
	static void writeNode(const YAML::Node& node, YAML::Emitter& emitter);
	
};


#endif // !LEVELLOADER

