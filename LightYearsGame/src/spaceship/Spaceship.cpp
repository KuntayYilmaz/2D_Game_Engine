#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld,texturePath },
		m_velocity{},
		m_HealthComp{ 100.f, 100.f },
		m_BlinkTime{0},
		m_BlinkDuration{0.2f},
		m_BlinkColorOffset{255,0,0,255}
	{
	}
	
	void Spaceship::Tick(float deltaTime)
	{ 
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);

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
		m_HealthComp.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
		m_HealthComp.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::Blow);
	}

	void Spaceship::ApplyDamage(float amt)
	{
		m_HealthComp.ChangeHealth(-amt);
	}

	void Spaceship::Blink()
	{
		if (m_BlinkTime == 0)
		{
			m_BlinkTime = m_BlinkDuration;
		}
	}

	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (m_BlinkTime > 0)
		{
			m_BlinkTime -= deltaTime;
			m_BlinkTime = m_BlinkTime > 0 ? m_BlinkTime : 0.f;

			GetSprite().setColor(LerpColor(sf::Color::White,m_BlinkColorOffset,m_BlinkTime));
		}
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{
		
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{
		Blink();
	}

	void Spaceship::Blow()
	{
		Explosion* exp = new Explosion();
		exp->SpawnExplosion(GetWorld(), GetActorLocation());
		Destroy();
		delete exp;
	}
}