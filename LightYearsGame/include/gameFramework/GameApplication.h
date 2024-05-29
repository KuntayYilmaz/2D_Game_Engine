#pragma once
#include <framework/Application.h>

namespace ly
{
	class Actor;
	class PlayerSpaceship;
	class GameApplication : public Application
	{

	public:
		GameApplication();

	private:
		void Tick(float deltaTime);
		weak<PlayerSpaceship> testSpaceship;
	};
}