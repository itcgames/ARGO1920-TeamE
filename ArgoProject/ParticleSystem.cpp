#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const std::string& currentState, int numofParticles, Type typeID)
{
	m_currentState = currentState;
	ChooseType(typeID,numofParticles);
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
			m_particles[i]->update();
			if (m_particles[i]->Alive() == false)
			{
				m_particles[i] = nullptr;
				m_particles.erase(m_particles.begin() + i);
			}
		}
	}
}

void ParticleSystem::render()
{
	if (m_currentState == "PLAY")
	{
		for (int i = 0; i < m_particles.size(); i++)
		{
			m_particles[i]->render();
		}
	}
}

void ParticleSystem::ChooseType(Type typeID, int numofParticles)
{
	if (typeID == Type::EXPLOSION)
	{
		for (int i = 0; i < numofParticles; i++)
		{
			m_particles.push_back(std::make_unique<Particle>(m_currentState, 1, disperseInCircle() + Vector2(1000, 600), Vector2(GenerateRandomNumber(-1.0, 1.0), GenerateRandomNumber(-1.0, 1.0))));
		}
	}

	if (typeID == Type::BLOOD)
	{
		for (int i = 0; i < numofParticles; i++)
		{
			m_particles.push_back(std::make_unique<Particle>(m_currentState, 0.1, disperseInCircle() + Vector2(1000, 600), Vector2(GenerateRandomNumber(-2.0, 2.0), GenerateRandomNumber(-2.0, 2.0))));
		}
	}
}

Vector2 ParticleSystem::disperseInCircle()
{
	double a = GenerateRandomNumber(0,2) * 2 * 3.14;
	double r = 50 * sqrt(GenerateRandomNumber(0,2));

	double x = r * cos(a);
	double y = r * sin(a);

	return Vector2(x, y);
}

double ParticleSystem::GenerateRandomNumber(double min, double max)
{
	std::random_device m_randDev;
	std::mt19937 mt(m_randDev());
	std::uniform_real_distribution<double> dist(min, max);
	return dist(mt);
}
