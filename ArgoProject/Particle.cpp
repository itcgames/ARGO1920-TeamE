#include "Particle.h"

Particle::Particle(const std::string& currentState, int maxAliveTime, Vector2 pos)
{
	m_currentState = currentState;
	MAX_PARTICLE_LIFE = maxAliveTime;

	m_particle.x = pos.x;
	m_particle.y = pos.y;


	SDL_Surface* surface = IMG_Load("Assets/Tiles/tile.png");
	m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surface);
	SDL_FreeSurface(surface);

	m_particle.w = 10;
	m_particle.h = 10;
	m_alive = true;
}

Particle::~Particle()
{
}

void Particle::CreateParticle()
{
	std::cout << "Particle Alive" << std::endl;
	m_alive = true;
}

void Particle::update()
{
	if (Alive())
	{
		std::cout << " Alive " << std::endl;
	}
	else
	{
		std::cout << " Dead " << std::endl;
	}

}

void Particle::render()
{
		SDL_RenderCopy(Renderer::Instance()->getRenderer(), m_texture, NULL, &m_particle);
}

bool Particle::Alive()
{
	if (m_currentState == "PLAY")
	{
		if (m_alive)
		{
			m_timeAlive++;

			if ((m_timeAlive / 60) > MAX_PARTICLE_LIFE)
			{
				m_timeAlive = 0;
				m_alive = false;
			}
			else
			{
				m_alive = true;
			}
		}
	}

	return m_alive;
}
