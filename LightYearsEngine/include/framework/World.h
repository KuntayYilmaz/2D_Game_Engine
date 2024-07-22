#pragma once
#include "framework/Core.h"
#include "SFML/Graphics.hpp"
#include "framework/Object.h"

namespace ly
{

	class Actor;
	class Application;
	class World : public Object
	{
	public:
		
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		World(Application* owningApp);
		virtual ~World();

		template<typename ActorType,typename... Args>
		weak<ActorType> SpawnActor(Args... args);

		sf::Vector2u GetWindowSize() const;
		void CleanCycle();
	private:
		
		
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		
		Application* m_OwningApp;
		bool m_BeganPlay;

		List<shared<Actor>> m_Actors;
		List<shared<Actor>> m_pendingActors;
	};
	
	template<typename ActorType, typename... Args>
	weak<ActorType> World::SpawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType(this, args...) };
		m_pendingActors.push_back(newActor);
		return newActor;	
	}

}