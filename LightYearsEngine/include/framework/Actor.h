#pragma once
#include "SFML/Graphics.hpp"
#include "framework/Object.h" 
#include "framework/Core.h"

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

		World* GetWorld() const { return m_OwningWorld; }

		bool IsActorOutOfWindowBounds() const;
	private:
		World* m_OwningWorld;
		bool m_BeganPlay;

		void CenterPivot();
		sf::Sprite m_Sprite;
		shared<sf::Texture> m_Texture;

	};

}