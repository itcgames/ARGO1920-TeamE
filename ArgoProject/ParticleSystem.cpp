#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const std::string& currentState)
{
	m_currentState = currentState;
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::update()
{
	if (m_currentState == "PLAY")
	{
		if (m_particles.size() < MAX_PARTICLES)
		{
			m_particles.push_back(std::make_unique<Particle>(m_currentState, 5, Vector2((rand() % 1000 + 1), (rand() % 1000 + 1))));
		}
		std::cout << m_particles.size() << std::endl;

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
