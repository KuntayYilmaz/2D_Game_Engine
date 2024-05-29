#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace ly
{
	HealthComponent::HealthComponent(float health, float maxHealth)
		:m_Health{health},
		m_MaxHealth{maxHealth}
	{
	}

	void HealthComponent::ChangeHealth(float amt)
	{
		if (amt == 0) return;
		if (m_Health == 0) return;

		m_Health += amt;
		if (m_Health < 0)
		{
			m_Health = 0;
		}

		if (m_Health > m_MaxHealth)
		{
			m_Health = m_MaxHealth;
		}

		if (amt < 0)
		{
			TakenDamage(-amt);
			if (m_Health <= 0)
			{
				HealthEmpty();
			}
		}
		

		onHealthChanged.Broadcast(amt, m_Health, m_MaxHealth);
	}

	void HealthComponent::TakenDamage(float amt)
	{
		onTakenDamage.Broadcast(amt, m_Health, m_MaxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		onHealthEmpty.Broadcast();
	}

	void HealthComponent::HealthRegen(float amt)
	{

	}

}