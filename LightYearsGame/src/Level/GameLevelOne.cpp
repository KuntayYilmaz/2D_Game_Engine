#include "Level/GameLevelOne.h"
#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "player/PlayerSpaceship.h"
#include "framework/AssetManager.h"
#include "Enemy/Vanguard.h"
#include "framework/TimeManager.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
		testSpaceship = SpawnActor<PlayerSpaceship>();
		testSpaceship.lock()->setActorLocation(sf::Vector2f{ 300.f,490.f });
		

		weak<Vanguard> enemySpaceship = SpawnActor<Vanguard>();
		enemySpaceship.lock()->setActorLocation(sf::Vector2f{ 300.f,100.f });
		
		
	}

	void GameLevelOne::BeginPlay()
	{
		TimeManager::Get().SetTimer(GetWeakRef(),&GameLevelOne::TimerCallBack,2);
	}

	void GameLevelOne::TimerCallBack()
	{
		LOG("Callback called");
	}

}