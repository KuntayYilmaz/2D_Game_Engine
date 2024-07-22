#pragma once
#include "Enemy/EnemySpaceship.h"


namespace ly
{
	class LaserShooter;
	class Vanguard : public EnemySpaceship
	{
	public:
		Vanguard(World* owningWorld, const std::string& texturePath = "Nairan/Designs-Base/PNGs/Nairan - Dreadnought - Base.png",const sf::Vector2f& velocity = {0.f, 50.f});
		virtual void Tick(float deltaTime) override;
	private:
		virtual void Shoot() override;
		unique<LaserShooter> m_Shooter;

	};
}