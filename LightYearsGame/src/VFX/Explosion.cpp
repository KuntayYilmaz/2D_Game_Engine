
#include "framework/World.h"
#include "framework/MathUtility.h"
#include "VFX/Particle.h"
#include "VFX/Explosion.h"

namespace ly
{
	Explosion::Explosion(int particleAmt, float lifeTimeMin, float lifeTimeMax, float sizeMin, float sizeMax, float speedMin, float speedMax, const List<std::string>& particleImagePaths)
		:m_ParticleAmt{ particleAmt },
		m_LifeTimeMin{ lifeTimeMin },
		m_LifeTimeMax{ lifeTimeMax },
		m_SizeMin{ sizeMin },
		m_SizeMax{ sizeMax },
		m_SpeedMin{ speedMin },
		m_SpeedMax{ speedMax },
		m_ParticleImagePaths{ particleImagePaths }
	{
	}

	void Explosion::SpawnExplosion(World* world, const sf::Vector2f& location)
	{
		if (!world)
		{
			return;
		}

		for (int i = 0; i < m_ParticleAmt; ++i)
		{
			std::string particleImagePath = m_ParticleImagePaths[(int)RandomRange(0, m_ParticleImagePaths.size())];
			weak<Particle> newParticle = world->SpawnActor<Particle>(particleImagePath);

			newParticle.lock()->RandomLifeTime(m_LifeTimeMin, m_LifeTimeMax);
			newParticle.lock()->setActorLocation(location);
			newParticle.lock()->RandomSize(m_SizeMin, m_SizeMax);
			newParticle.lock()->RandomVelocity(m_SpeedMin, m_SpeedMax);


		}
	}


	
}
