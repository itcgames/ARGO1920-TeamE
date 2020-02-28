#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const std::string& currentState, RenderSystem* t_rs)
{
	m_rs = t_rs;
	m_currentState = currentState;
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update()
{
	if (m_currentState == "PLAY")
	{
		for (int i = 0; i < m_particles.size(); i++)
		{
			if (m_particles[i] != nullptr)
			{
				m_particles[i]->update();
				if (m_particles[i]->Alive() == false)
				{
					m_particles[i]->getEntity()->getComponent<ActiveComponent>(6)->setIsActive(false);
					m_rs->deleteEntity(m_particles[i]->getEntity());
					m_particles[i] = nullptr;
					m_particles.erase(m_particles.begin() + i);
				}
			}
		}
	}
}


void ParticleSystem::AddParticles(Vector2 pos = Vector2{ 0,0 }, Type typeID = Type::EXPLOSION, int numofParticles = MAX_PARTICLES, int size = 10, std::string fileName = "Assets/Tiles/tile.png")
{
	float timeToLive = 0;
	Vector2 position = pos;
	Vector2 velocity = { 0,0 };
	if (typeID == Type::EXPLOSION)
	{
		for (int i = 0; i < numofParticles; i++)
		{
			timeToLive = GenerateRandomNumber(0.9, 1);
			position = disperseInCircle(position + Vector2(25, 25), 50);
			velocity = Vector2(GenerateRandomNumber(-4.0, 4.0), GenerateRandomNumber(-4.0, 4.0));

			m_particles.push_back(std::make_unique<Particle>(m_currentState, timeToLive,size,fileName, position, velocity, m_rs));
		}
	}

	if (typeID == Type::BLOOD)
	{
		for (int i = 0; i < numofParticles; i++)
		{
			timeToLive = GenerateRandomNumber(0.1, 0.2);
			position = disperseInCircle(position + Vector2(50, 0), 100);
			velocity = Vector2(GenerateRandomNumber(-0.2, 0.2), GenerateRandomNumber(-0.2, 0.2));

			m_particles.push_back(std::make_unique<Particle>(m_currentState, timeToLive, size, fileName, position, velocity, m_rs));
		}
	}

	if (typeID == Type::BARSEFFECT)
	{
		for (int i = 0; i < numofParticles; i++)
		{
			timeToLive = GenerateRandomNumber(0.1, 0.4);
			position = disperseInRect(Vector2(1900, 1990), 1000, 5);
			velocity = Vector2(GenerateRandomNumber(-0.1, 0.1), GenerateRandomNumber(-0.1, 0.1));

			m_particles.push_back(std::make_unique<Particle>(m_currentState, timeToLive, size, fileName, position, velocity, m_rs));
		}
	}

	if (typeID == Type::TRAIL)
	{
		if (m_particles.size() < numofParticles)
		{
			timeToLive = GenerateRandomNumber(0.1, 0.4);
			position = disperseInRect(position + Vector2(50, 0), 100, 100);
			velocity = Vector2(GenerateRandomNumber(-3, 0), GenerateRandomNumber(-0.1, 0.1));

			m_particles.push_back(std::make_unique<Particle>(m_currentState, timeToLive, size, fileName, position, velocity, m_rs));
		}
	}
}


Vector2 ParticleSystem::disperseInCircle(Vector2 t_pos, int circleRadius)
{
	double a = GenerateRandomNumber(-2, 2) * 2 * 3.14;
	double r = circleRadius * sqrt(GenerateRandomNumber(-2, 2));

	double x = r * cos(a);
	double y = r * sin(a);

	return Vector2(t_pos.x + x, t_pos.y + y);
}

Vector2 ParticleSystem::disperseInRect(Vector2 pos, int width, int height)
{
	double x = GenerateRandomNumber(pos.x, (int)pos.x + width);
	double y = GenerateRandomNumber(pos.y, (int)pos.y + height);

	return Vector2(x, y);
}

double ParticleSystem::GenerateRandomNumber(double min, double max)
{
	std::random_device m_randDev;
	std::mt19937 mt(m_randDev());
	std::uniform_real_distribution<double> dist(min, max);
	return dist(mt);
}