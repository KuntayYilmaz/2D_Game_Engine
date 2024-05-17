#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

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
		ActorPrime = newWorld.lock()->SpawnActor<Actor>();
		ActorPrime.lock()->SetTexture("C:/dev/LightYears/LightYearsGame/assets/Nairan/Designs-Base/PNGs/Nairan-Battlecruiser-Base.png");
		
	}

}