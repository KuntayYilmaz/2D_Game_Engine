#include "framework/Actor.h"
#include "framework/Core.h"

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
		LOG("Actor destroyed\n"); 
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
		LOG("Actor started playing\n");
	}
	
	void Actor::Tick(float deltaTime)
	{
		LOG("Actor Ticking\n");
	}
	
	void Actor::SetTexture(const std::string& texturePath)
	{
		m_Texture.loadFromFile(texturePath);
		m_Sprite.setTexture(m_Texture);

		int textureWidth = m_Texture.getSize().x;
		int textureHeight = m_Texture.getSize().y;

		m_Sprite.setTextureRect(sf::IntRect{ sf::Vector2i{},sf::Vector2i{textureWidth,textureHeight} });
	}
	
	void Actor::Render(sf::RenderWindow& window)
	{
		if (isPendingDestroyed())
			return;

		window.draw(m_Sprite);
	}
}