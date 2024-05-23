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
		:Application{ 600,900, "Light Years", sf::Style::Titlebar | sf::Style::Close }
	{
		AssetManager::Get().setAssetRootDirectory(GetResourceDir());
		weak<World> newWorld = LoadWorld<World>();
		
		testSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testSpaceship.lock()->setActorLocation(sf::Vector2f{ 300.f,490.f });
		testSpaceship.lock()->setActorRotation(0.f);

		weak<Spaceship> enemySpaceship = newWorld.lock()->SpawnActor<Spaceship>();
		enemySpaceship.lock()->SetTexture("Nairan/Designs-Base/PNGs/Nairan-Battlecruiser-Base.png");
		enemySpaceship.lock()->setActorLocation(sf::Vector2f{ 400.f,100.f });
		
		counter = 0.f;
	
	}

	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;
		if (counter > 5.f)
		{
			if (!testSpaceship.expired())
			{
				testSpaceship.lock()->Destroy();
			}
		}
	}
}