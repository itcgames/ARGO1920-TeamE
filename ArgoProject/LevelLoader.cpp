#include "LevelLoader.h"

YAML::Node LevelLoader::m_baseNode; // Defines the static variable

/// <summary>
/// Operator to Load High Scores
/// </summary>
/// <param name="t_scoreDataNode">NOde containgin high score data</param>
/// <param name="t_score"> high score object</param>
void operator >> (const YAML::Node & t_scoreDataNode, HighScoreData & t_score)
{
	t_score.m_name = t_scoreDataNode["name"].as<std::string>();
	t_score.m_score = t_scoreDataNode["score"].as<int>();
}

void operator >> (const YAML::Node & t_statsDataNode, StatsData & t_value)
{
	t_value.m_class = t_statsDataNode["class"].as<std::string>();
	t_value.m_health = t_statsDataNode["health"].as<int>();
	t_value.m_strength = t_statsDataNode["strength"].as<int>();
	t_value.m_speed = t_statsDataNode["speed"].as<int>();
	t_value.m_gold = t_statsDataNode["gold"].as<int>();
	t_value.m_killCount = t_statsDataNode["killcount"].as<int>();
}

void operator >> (const YAML::Node& t_playerStatsDataNode, PlayerStatsData& t_value)
{
	t_value.m_class = t_playerStatsDataNode["class"].as<std::string>();
	t_value.m_health = t_playerStatsDataNode["health"].as<int>();
	t_value.m_strength = t_playerStatsDataNode["strength"].as<int>();
	t_value.m_speed = t_playerStatsDataNode["speed"].as<int>();
	t_value.m_gold = t_playerStatsDataNode["gold"].as<int>();
	t_value.m_killCount = t_playerStatsDataNode["killcount"].as<int>();
}

void operator >> (const YAML::Node & t_levelDataNode, LevelData & t_level)
{
	const YAML::Node& statsNode = t_levelDataNode["Stats"].as<YAML::Node>();
	//loop through all of the nodes in the scoresNode and load all of the data
	auto size = statsNode.size();
	for (unsigned i = 0; i < statsNode.size(); i++)
	{
		StatsData stats;
		statsNode[i] >> stats;
		t_level.m_stats.push_back(stats);

		//platform.m_base.setSize(sf::Vector2f(100, 20));
		//platform.m_position.x = groundPoints.m_position.x;
		//platform.m_position.y = groundPoints.m_position.y;
		//t_level.m_platforms.push_back(platform);
		//m_position = m_level.m_level1.m_startPointPos;
		//m_base.setSize(sf::Vector2f(100, 20));
		//m_base.setFillColor(sf::Color::Red);
		//m_base.setPosition(m_position);

	}
}


void operator >> (const YAML::Node & t_levelNode, GameData & t_level)
{
	////make a new node pointing at the base nodes highscores node
	 const YAML::Node& scoresNode = t_levelNode["Highscores"].as<YAML::Node>();

	////loop through all of the nodes in the scoresNode and load all of the data
	 auto ssize = scoresNode.size();
	for (unsigned i = 0; i < scoresNode.size(); ++i)
	{
		HighScoreData scores;
		scoresNode[i] >> scores;
		t_level.m_scores.push_back(scores);
	}

	const YAML::Node& playerStatsNode = t_levelNode["Player"].as<YAML::Node>();

	//loop through all of the nodes in the scoresNode and load all of the data
	auto psize = playerStatsNode.size();
	for (unsigned i = 0; i < playerStatsNode.size(); ++i)
	{
		PlayerStatsData stats;
		playerStatsNode[i] >> stats;
		t_level.m_playerStats.push_back(stats);
	}

	t_levelNode["Presets"] >> t_level.m_presets;
	t_levelNode["Level2"] >> t_level.m_level2;
	t_levelNode["Level3"] >> t_level.m_level3;
}

bool LevelLoader::load(int t_nr, GameData & t_level)
{
	std::stringstream ss;
	ss << "RESOURCES//YAML//";
	ss << t_nr;
	ss << ".yaml";

	try
	{
		m_baseNode = YAML::LoadFile(ss.str());
		if (m_baseNode.IsNull())
		{
			std::string msg("No file found :" + ss.str());
			throw std::exception(msg.c_str());	
		}
		m_baseNode >> t_level;
	}
	catch (YAML::ParserException & e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}

bool LevelLoader::load(std::string t_fileName, GameData & t_level)
{
	std::stringstream ss;
	ss << t_fileName;

	try
	{
		m_baseNode = YAML::LoadFile(ss.str());
		if (m_baseNode.IsNull())
		{
			std::string msg("No file found :" + ss.str());
			throw std::exception(msg.c_str());
		}
		m_baseNode >> t_level;
	}
	catch (YAML::ParserException & e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}


void LevelLoader::write(std::string t_playerName[], int t_playerScore[])
{
	 YAML::Node scoresNode = m_baseNode["Highscores"].as<YAML::Node>();
	for (int i = 0; i < 10; i++)
	{
		scoresNode[i]["name"] = t_playerName[i];		
		scoresNode[i]["score"] = t_playerScore[i];
	}
	
	//m_baseNode["Highscores"]["name"] = "Jim";// edit one of the nodes 
	//auto name = m_baseNode["Highscores"]["name"].as<std::string>();
	std::string file = ".\\Assets\\YAML\\level1.yaml";
	std::ofstream fout(file); // This is the path to the YAML file
	//fout << m_baseNode; // dump it back into the file


	YAML::Emitter emitter;
	writeNode(m_baseNode, emitter);
	fout << emitter.c_str() << std::endl;
	//std::cout << emitter.c_str() << std::endl;
	fout.close();
}

void LevelLoader::writeToPlayer(std::string t_class, int t_health, int t_strength, int t_speed, int t_gold, int t_killCount)
{
	YAML::Node playerStatsNode = m_baseNode["Player"].as<YAML::Node>();
	for (int i = 0; i < 1; i++)
	{
		playerStatsNode[i]["class"] = t_class;
		playerStatsNode[i]["health"] = t_health;
		playerStatsNode[i]["strength"] = t_strength;
		playerStatsNode[i]["speed"] = t_speed;
		playerStatsNode[i]["gold"] = t_gold;
		playerStatsNode[i]["killcount"] = t_killCount;
	}
	//m_baseNode["Player"]["class"] = t_class;
	//auto name = m_baseNode["Player"]["class"].as<std::string>();
	//m_baseNode["Player"]["health"] = t_health;
	//auto health = m_baseNode["Player"]["health"].as<int>();
	//m_baseNode["Player"]["strength"] = t_strength;
	//auto strength = m_baseNode["Player"]["strength"].as<int>();
	//m_baseNode["Player"]["speed"] = t_speed;
	//auto speed = m_baseNode["Player"]["speed"].as<int>();
	//m_baseNode["Player"]["gold"] = t_gold;
	//auto gold = m_baseNode["Player"]["gold"].as<int>();
	//m_baseNode["Player"]["killcount"] = t_killCount;
	//auto killcount = m_baseNode["Player"]["killcount"].as<int>();

	//m_baseNode["Highscores"]["name"] = "Jim";// edit one of the nodes 
	//auto name = m_baseNode["Highscores"]["name"].as<std::string>();
	std::string file = ".\\Assets\\YAML\\level1.yaml";
	std::ofstream fout(file); // This is the path to the YAML file
	//fout << m_baseNode; // dump it back into the file


	YAML::Emitter emitter;
	writeNode(m_baseNode, emitter);
	fout << emitter.c_str() << std::endl;
	//std::cout << emitter.c_str() << std::endl;
	fout.close();
}


// Recursive helper function that does all the work
void LevelLoader::writeNode(const YAML::Node& node, YAML::Emitter& emitter)
{
	switch (node.Type())
	{
	case YAML::NodeType::Sequence:
	{
		emitter << YAML::BeginSeq;
		auto size = node.size();
		for (size_t i = 0; i < node.size(); i++)
		{			
			writeNode(node[i], emitter);
		}
		emitter << YAML::EndSeq;
		break;
	}
	case YAML::NodeType::Map:
	{
		emitter << YAML::BeginMap;

		// First collect all the keys
		std::vector<std::string> keys(node.size());
		int key_it = 0;
		for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
		{
			keys[key_it++] = it->first.as<std::string>();
		}

		// Then sort them
		std::sort(keys.begin(), keys.end());

		// Then emit all the entries in sorted order.
		for (size_t i = 0; i < keys.size(); i++)
		{
			emitter << YAML::Key;
			emitter << keys[i];
			emitter << YAML::Value;
			writeNode(node[keys[i]], emitter);
		}
		emitter << YAML::EndMap;
		break;
	}
	default:
		emitter << node;
		break;
	}
}
