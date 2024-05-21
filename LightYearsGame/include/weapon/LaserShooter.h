#pragma once
#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace ly
{
	class LaserShooter : public Shooter
	{
	public:
		LaserShooter(Actor* owner, float cooldownTime = 1.f);
		virtual bool IsOnCooldown() const override;

	private:
		virtual void ShootImpl() override;

		sf::Clock m_CooldownClock;
		float m_CooldownTime;
	};
}