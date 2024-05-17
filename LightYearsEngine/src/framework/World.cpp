#include "SFML/Graphics.hpp"
#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"


namespace ly
{
	World::World(Application* owningApp)
		:m_OwningApp{ owningApp },
		m_BeganPlay{false},
		m_Actors{},
		m_pendingActors{}
	{

	}

	void World::BeginPlayInternal()
	{
		if (!m_BeganPlay)
		{
			m_BeganPlay = true;
			BeginPlay();
		}

	}
	
	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : m_pendingActors)
		{
			m_Actors.push_back(actor);
			actor->BeginPlayInternal();
		}

		m_pendingActors.clear(); 

		for (auto it = m_Actors.begin(); it != m_Actors.end();)
		{
			if (it->get()->isPendingDestroyed())
			{
				it = m_Actors.erase(it);
			}
			else
			{
				it->get()->TickInternal(deltaTime);
				++it;
			}
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : m_Actors)
		{
			actor->Render(window);
		}
	}
	
	World::~World()
	{

	}
	
	void World::BeginPlay()
	{
		
	}
	
	void World::Tick(float deltaTime)
	{
		
	}
}
