#pragma once
#include "spaceship/Spaceship.h"


namespace ly
{
	class LaserShooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "Nairan/Designs-Base/PNGs/Nairan-Battlecruiser-Base.png");
		
		virtual void Tick(float deltaTime) override; 
		void SetSpeed(float newSpeed) { m_speed = newSpeed; }
		float GetSpeed() const { return m_speed; }

		virtual void Shoot() override;
	private:
		void HandleInput();
		void ApplyInput(float deltaTime);
		void NormalizeInput();
		void ClampInputOnEdge();

		sf::Vector2f m_moveInput; 
		float m_speed;


		unique<LaserShooter> m_Shooter;
	};
}