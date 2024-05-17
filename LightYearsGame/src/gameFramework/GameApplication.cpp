#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		:Application{ 900,900, "Light Years", sf::Style::Titlebar | sf::Style::Close }
	{
		weak<World> newWorld = LoadWorld<World>();
		m_ActorPrime = newWorld.lock()->SpawnActor<Actor>();
		m_ActorPrime.lock()->SetTexture(GetResourceDir() + "Nairan/Designs-Base/PNGs/Nairan - Dreadnought - Base.png");
		m_ActorPrime.lock()->setActorLocation(sf::Vector2f{ 450.f,450.f });
		
	}

}