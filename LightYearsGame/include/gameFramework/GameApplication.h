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

		weak<PlayerSpaceship> testSpaceship;
	};
}