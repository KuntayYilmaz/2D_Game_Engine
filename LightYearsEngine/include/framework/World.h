#pragma once
#include "framework/Core.h"
#include "SFML/Graphics.hpp"

namespace ly
{

	class Actor;
	class Application;
	class World
	{
	public:
		
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		World(Application* owningApp);
		virtual ~World();

		template<typename ActorType>
		weak<ActorType> SpawnActor();

		sf::Vector2u GetWindowSize() const;

	private:
		
		//FUNCTIONS
		void BeginPlay();
		void Tick(float deltaTime);

		//VARIABLES
		Application* m_OwningApp;
		bool m_BeganPlay;

		List<shared<Actor>> m_Actors;
		List<shared<Actor>> m_pendingActors;
	};
	
	template<typename ActorType>
	weak<ActorType> World::SpawnActor()
	{
		shared<ActorType> newActor{ new ActorType{this} };
		m_pendingActors.push_back(newActor);
		return newActor;	
	}

}