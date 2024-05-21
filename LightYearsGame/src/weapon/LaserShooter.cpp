#include "weapon/LaserShooter.h"
#include "framework/Core.h"
#include "weapon/Bullet.h"
#include "framework/World.h"


namespace ly
{
	LaserShooter::LaserShooter(Actor* owner, float cooldownTime)
		:Shooter{ owner },
		m_CooldownClock{},
		m_CooldownTime{cooldownTime}
	{
	}

	bool LaserShooter::IsOnCooldown() const
	{
		if (m_CooldownClock.getElapsedTime().asSeconds() > m_CooldownTime)
		{
			return false;
		}
		
		return true;
	}

	void LaserShooter::ShootImpl()
	{
		m_CooldownClock.restart();
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(),"Nairan/Weapon Effects - Projectiles/PNGs/Nairan - Bolt.png");
		newBullet.lock()->setActorLocation(GetOwner()->GetActorLocation());
		newBullet.lock()->setActorRotation(GetOwner()->GetActorRotation());
		
		
	}
}