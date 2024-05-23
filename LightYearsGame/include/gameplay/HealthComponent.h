#pragma once


namespace ly
{
	class HealthComponent
	{
	public:
		HealthComponent(float health, float maxHealth);
		void ChangeHealth(float amt);
		float GetHealth() const { return m_Health; }
		float GetMaxHealth() const { return m_MaxHealth; }

	private:
		void TakenDamage(float amt);
		void HealthEmpty();
		void HealthRegen(float amt);


		float m_Health;
		float m_MaxHealth;
	};
}