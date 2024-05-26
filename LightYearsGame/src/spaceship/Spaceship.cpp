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

		m_HealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
		m_HealthComp.onHealthChanged.Broadcast(11, 89, 100);
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{
		LOG("Health changed by: %f, and is now: %f/%f", amt, health, maxHealth);
	}
}