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

void operator >> (const YAML::Node & t_groundDataNode, GroundData & t_ground)
{
	t_ground.m_position = Vector2(t_groundDataNode["position"]["x"].as<float>(), t_groundDataNode["position"]["y"].as<float>());
}

void operator >> (const YAML::Node & t_levelDataNode, LevelData & t_level)
{
	const YAML::Node& groundNode = t_levelDataNode["Ground"].as<YAML::Node>();
	for (unsigned i = 0; i < groundNode.size(); i++)
	{
		GroundData groundPoints;
		groundNode[i] >> groundPoints;
		t_level.m_groundPoints.push_back(groundPoints);

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
	//make a new node pointing at the base nodes highscores node
	 const YAML::Node& scoresNode = t_levelNode["Highscores"].as<YAML::Node>();

	//loop through all of the nodes in the scoresNode and load all of the data
	 auto size = scoresNode.size();
	for (unsigned i = 0; i < scoresNode.size(); ++i)
	{
		HighScoreData scores;
		scoresNode[i] >> scores;
		t_level.m_scores.push_back(scores);
	}

	t_levelNode["Level1"] >> t_level.m_level1;
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
