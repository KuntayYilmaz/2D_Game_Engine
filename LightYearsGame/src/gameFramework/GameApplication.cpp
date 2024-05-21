#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "player/PlayerSpaceship.h"
#include "framework/AssetManager.h"
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
		AssetManager::Get().setAssetRootDirectory(GetResourceDir());
		weak<World> newWorld = LoadWorld<World>();
		
		testSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testSpaceship.lock()->setActorLocation(sf::Vector2f{ 450.f,450.f });
		testSpaceship.lock()->setActorRotation(0.f);
	
		
		
	}
	


}