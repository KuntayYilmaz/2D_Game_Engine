#pragma once
#include <string>
#include "framework/Core.h"


namespace ly
{
	class World;
	class Explosion
	{
	public:
		Explosion(int particleAmt = 5,
			float lifeTimeMin = 10,
			float lifeTimeMax = 20,
			float sizeMin = 1,
			float sizeMax = 1.5,
			float speedMin = 100,
			float speedMax = 200,
			
			const List<std::string>& particleImagePaths =
			{
				"Nairan/Destruction/PNGs/Particle1.png",
				"Nairan/Destruction/PNGs/Particle2.png",
				"Nairan/Destruction/PNGs/Particle3.png"
			}	

			);

		void SpawnExplosion(World* world,const sf::Vector2f& location);
		
	private:
		int m_ParticleAmt;
		float m_LifeTimeMin;
		float m_LifeTimeMax;
		float m_SizeMin;
		float m_SizeMax;
		float m_SpeedMin;
		float m_SpeedMax;
		List<std::string> m_ParticleImagePaths;
	};
}