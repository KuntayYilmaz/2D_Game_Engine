#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Object.h" 
#include "framework/Core.h"

class b2Body;
namespace ly
{
	class World;

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();
		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		
		void SetTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);

		void setActorLocation(const sf::Vector2f& newLoc);
		void setActorRotation(float newRot);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt);

		sf::Vector2u GetWindowSize() const;

		sf::Vector2f GetActorLocation() const;
		sf::FloatRect GetActorBounds() const;

		sf::FloatRect GetActorGlobalBounds() const;

		float GetActorRotation() const;
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;

		World* GetWorld() { return m_OwningWorld; }
		const World* GetWorld() const { return m_OwningWorld; }

		bool IsActorOutOfWindowBounds() const;

		void SetEnablePhysics(bool enable);
		virtual void OnActorBeginOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);

		virtual void Destroy() override;


		static uint8 GetNeutralTeamId() { return m_NeutralTeamID; }
		uint8 GetTeamID() const { return m_TeamID; }
		void SetTeamID(uint8 teamID) { m_TeamID = teamID; }
		bool IsOtherEnemy(Actor* other) const;

		virtual void ApplyDamage(float amt);

		sf::Sprite& GetSprite() { return m_Sprite; }
		const sf::Sprite& GetSprite() const { return m_Sprite; }


	private:
		void InitializePhysics();
		void UnInitializePhysics();
		void UpdatePhysicsBodyTransform();
		void CenterPivot();



		World* m_OwningWorld;
		bool m_BeganPlay;

		sf::Sprite m_Sprite;
		shared<sf::Texture> m_Texture;

		b2Body* m_PhysicsBody;
		bool m_PhysicsEnabled;

		uint8 m_TeamID;

		const static uint8 m_NeutralTeamID = 255;
	};

}