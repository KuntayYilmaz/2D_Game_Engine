#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
	class Application
	{
	public:
		Application();
		void Run();
		void Render();
	private:
		void Tick(float deltaTime);

		sf::RenderWindow m_window;
		float m_TargetFrameRate;
		sf::Clock m_TickClock;
	};
}