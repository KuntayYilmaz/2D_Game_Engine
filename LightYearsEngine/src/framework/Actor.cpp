#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h",
#include "framework/MathUtility.h"
#include "framework/World.h"


namespace ly
{
	Actor::Actor(World* owningWorld,const std::string& texturePath)
		: m_OwningWorld{ owningWorld },
		m_BeganPlay{false},
		m_Sprite{},
		m_Texture{}
	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		LOG("Actor Destroyed\n"); 
	}
	
	void Actor::BeginPlayInternal()
	{
		if (!m_BeganPlay)
		{
			m_BeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!isPendingDestroyed())
		{
			Tick(deltaTime);
		}
	}
	
	void Actor::BeginPlay()
	{

	}
	
	void Actor::Tick(float deltaTime)
	{
		
	}
	
	void Actor::SetTexture(const std::string& texturePath)
	{

		m_Texture = AssetManager::Get().LoadTexture(texturePath);
		if (!m_Texture) return;

		m_Sprite.setTexture(*m_Texture);

		int textureWidth = m_Texture->getSize().x;
		int textureHeight = m_Texture->getSize().y;
		m_Sprite.setTextureRect(sf::IntRect{ sf::Vector2i{},sf::Vector2i{textureWidth,textureHeight} });
		CenterPivot();
	}
	
	void Actor::Render(sf::RenderWindow& window)
	{
		if (isPendingDestroyed())
			return;

		window.draw(m_Sprite);
	}



	void Actor::setActorLocation(const sf::Vector2f& newLoc)
	{
		m_Sprite.setPosition(newLoc);
	}

	void Actor::setActorRotation(float newRot)
	{
		m_Sprite.setRotation(newRot);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		setActorLocation(GetActorLocation() + offsetAmt);
	}

	void Actor::AddActorRotationOffset(float offsetAmt)
	{
		setActorRotation(GetActorRotation() + offsetAmt);
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return m_OwningWorld->GetWindowSize();
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return m_Sprite.getPosition();
	}

	sf::FloatRect Actor::GetActorBounds() const
	{
		return m_Sprite.getGlobalBounds();
	}

	float Actor::GetActorRotation() const
	{
		return m_Sprite.getRotation();
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.f);
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}
}