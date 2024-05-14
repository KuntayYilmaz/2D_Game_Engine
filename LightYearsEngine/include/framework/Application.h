#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
	class Application
	{
	public:
		Application();
		void Run();

	private:
		void RenderInternal(int x,int y);
		void TickInternal(float deltaTime);
		
		virtual void Render(int x,int y);
		virtual void Tick(float deltaTime);


		sf::RenderWindow m_window;
		float m_TargetFrameRate;
		sf::Clock m_TickClock;
	};
}