#include "VFX/Particle.h"
#include "framework/MathUtility.h"

namespace ly
{
	Particle::Particle(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld,texturePath }, m_Velocity{}, m_LifeTime{ 1.f }, m_Timer{}
	{
	}

	void Particle::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		Move(deltaTime);
		Fade(deltaTime);

		if (m_Timer.getElapsedTime().asSeconds() >= m_LifeTime)
		{
			Destroy();
		}
	}

	void Particle::RandomVelocity(float minSpeed, float maxSpeed)
	{
		m_Velocity = RandomUnitVector() * RandomRange(minSpeed, maxSpeed);
	}

	void Particle::RandomSize(float min, float max)
	{
		float randScale = RandomRange(min, max);
		GetSprite().setScale(randScale, randScale);
	}

	void Particle::RandomLifeTime(float min, float max)
	{
		m_LifeTime = RandomRange(min, max);
	}

	void Particle::Move(float deltaTime)
	{
		AddActorLocationOffset(m_Velocity * deltaTime);
	}

	void Particle::Fade(float deltaTime)
	{
		float elapsedTime = m_Timer.getElapsedTime().asSeconds();
		GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime / m_LifeTime));
		GetSprite().setScale(LerpVector(GetSprite().getScale(), sf::Vector2f{ 0,0 }, elapsedTime / m_LifeTime));

	}
}

