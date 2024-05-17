#pragma once
#include <framework/Application.h>

namespace ly
{
	class Actor;
	class GameApplication : public Application
	{

	public:
		GameApplication();
	private:

		weak<Actor> m_ActorPrime;
	};
}