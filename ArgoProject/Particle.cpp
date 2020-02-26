#include "Particle.h"

Particle::Particle(const std::string& currentState, int maxAliveTime, Vector2 pos, Vector2 t_velocity = Vector2(0, 0), RenderSystem* t_rs = NULL)
{
	m_particleRect = new SDL_Rect();

	m_currentState = currentState;
	MAX_PARTICLE_LIFE = maxAliveTime;

	m_direction.x = t_velocity.x;
	m_direction.y = t_velocity.y;

	m_particleRect->x = pos.x;
	m_particleRect->y = pos.y;

	m_pos.x = pos.x;
	m_pos.y = pos.y;


	SDL_Surface* surface = IMG_Load("Assets/Tiles/tile.png");
	m_texture = SDL_CreateTextureFromSurface(Render::Instance()->getRenderer(), surface);
	SDL_FreeSurface(surface);

	m_particleRect->w = size;
	m_particleRect->h = size;

	m_particle = new Entity();

	m_pc = new PositionComponent(Vector2(m_particleRect->x, m_particleRect->y), 1);
	m_sc = new SpriteComponent(m_texture, m_particleRect, 2);
	m_ac = new ActiveComponent(true, 6);

	m_particle->addComponent<PositionComponent>(m_pc, 1);
	m_particle->addComponent<SpriteComponent>(m_sc, 2);
	m_particle->addComponent<ActiveComponent>(m_ac, 6);
	m_particle->setID(-2);

	t_rs->addEntity(m_particle);

	m_alive = true;
}

Particle::~Particle()
{
	SDL_DestroyTexture(m_texture);
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


bool Particle::Alive()
{
	if (m_currentState == "PLAY")
	{
		if (m_alive)
		{
			m_timeAlive++;

			if ((m_timeAlive / 15) > MAX_PARTICLE_LIFE)
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
	m_pc->setPosition(newPos);
}

void Particle::setAngle(float t_angle)
{
}


