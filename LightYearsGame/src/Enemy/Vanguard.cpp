#include "Enemy/Vanguard.h"
#include "weapon/LaserShooter.h"

namespace ly
{
	Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		:EnemySpaceship{owningWorld,texturePath},
		m_Shooter{ new LaserShooter{this} }
	{
		SetVelocity(velocity);
		setActorRotation(180.f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void Vanguard::Shoot()
	{
		m_Shooter->Shoot();
	}
}