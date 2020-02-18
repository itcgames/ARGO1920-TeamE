#include "Particle.h"

Particle::Particle(const std::string& currentState, int maxAliveTime, Vector2 pos, Vector2 t_velocity = Vector2(0,0))
{
	m_currentState = currentState;
	MAX_PARTICLE_LIFE = maxAliveTime;

	m_direction.x = t_velocity.x;
	m_direction.y = t_velocity.y;

	m_particle.x = pos.x;
	m_particle.y = pos.y;

	m_pos.x = pos.x;
	m_pos.y = pos.y;


	SDL_Surface* surface = IMG_Load("Assets/blood.png");
	m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surface);
	SDL_FreeSurface(surface);

	m_particle.w = size;
	m_particle.h = size;
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
	m_pos += (m_direction * m_speed);
	setPosition(m_pos);
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

void Particle::setPosition(Vector2 newPos)
{
	m_particle.x = newPos.x;
	m_particle.y = newPos.y;
}

