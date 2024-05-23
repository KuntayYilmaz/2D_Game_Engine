#include "spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld,texturePath },
		m_velocity{},
		m_HealthComp{ 100.f, 100.f }
	{
	}
	
	void Spaceship::Tick(float deltaTime)
	{ 
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);

	}

	void Spaceship::SetVelocity(const sf::Vector2f& newVel)
	{
		m_velocity = newVel;
	}

	void Spaceship::Shoot()
	{
		
	}
	
	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();

		SetEnablePhysics(true);
	}
}