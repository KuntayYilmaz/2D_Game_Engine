#include "weapon/Bullet.h"

namespace ly
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		: Actor{world,texturePath},
		m_Owner{owner},
		m_Speed{speed},
		m_Damage{damage}
	{

	}

	void Bullet::SetSpeed(float newSpeed)
	{
		m_Speed = newSpeed;
	}

	void Bullet::SetDamage(float newDamage)
	{
		m_Damage = newDamage;
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);
		if(IsActorOutOfWindowBounds())
		{
			Destroy();
		}
	}

	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Bullet::Move(float deltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * m_Speed * deltaTime);
	}
}