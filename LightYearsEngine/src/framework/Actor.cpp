#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"


namespace ly
{
	Actor::Actor(World* owningWorld,const std::string& texturePath)
		: m_OwningWorld{ owningWorld },
		m_BeganPlay{false},
		m_Sprite{},
		m_Texture{},
		m_PhysicsBody{nullptr},
		m_PhysicsEnabled{false},
		m_TeamID{GetNeutralTeamId()}
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
		UpdatePhysicsBodyTransform();
	}

	void Actor::setActorRotation(float newRot)
	{
		m_Sprite.setRotation(newRot);
		UpdatePhysicsBodyTransform();
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

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return m_Sprite.getGlobalBounds();
	}

	float Actor::GetActorRotation() const
	{
		return m_Sprite.getRotation();
	}



	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation() - 90.f);
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation());
	}




	bool Actor::IsActorOutOfWindowBounds() const
	{
		float windowWidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;

		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorLocation = GetActorLocation();

		if (actorLocation.x < -width)
		{
			return true;
		}
		if (actorLocation.x > windowWidth + width)
		{
			return true;
		}
		if (actorLocation.y < -height)
		{
			return true;
		}
		if (actorLocation.y > windowHeight + height)
		{
			return true;
		}

		return false;
	}

	void Actor::SetEnablePhysics(bool enable)
	{
		m_PhysicsEnabled = enable;
		if (m_PhysicsEnabled)
		{
			InitializePhysics();
		}
		else
		{
			UnInitializePhysics();
		}
	}

	void Actor::OnActorBeginOverlap(Actor* other)
	{

	}

	void Actor::OnActorEndOverlap(Actor* other)
	{
		
	}

	void Actor::Destroy()
	{
		UnInitializePhysics();
		Object::Destroy();
	}

	bool Actor::IsOtherEnemy(Actor* other) const
	{
		if (GetTeamID() == GetNeutralTeamId() || other->GetTeamID() == GetNeutralTeamId())
		{
			return false;
		}
		
		return GetTeamID() != other->GetTeamID();

		
	}

	void Actor::ApplyDamage(float amt)
	{

	}

	void Actor::InitializePhysics()
	{
		if (!m_PhysicsBody)
		{
			m_PhysicsBody = PhysicsSystem::Get().AddListener(this);
		}
	}

	void Actor::UnInitializePhysics()
	{
		if(m_PhysicsBody)
		{
			PhysicsSystem::Get().RemoveListener(m_PhysicsBody);
			m_PhysicsBody = nullptr;
		}
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (m_PhysicsBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale };
			float rotation = DegreesToRadians(GetActorRotation());

			m_PhysicsBody->SetTransform(pos, rotation);
		}
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}
}