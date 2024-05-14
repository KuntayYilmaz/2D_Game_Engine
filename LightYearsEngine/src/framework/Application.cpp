#include "framework/Application.h"
#include <framework/Core.h>

namespace ly
{
	Application::Application()
		: m_window{ sf::VideoMode(800,800),"Light Years"},
		m_TargetFrameRate{144.f},
		m_TickClock{}
	{
			
	}
	void Application::Run()
	{
		m_TickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / m_TargetFrameRate;
		int x{ 0 };
		int y{ 0 };
		while (m_window.isOpen())
		{
			
			sf::Event windowEvent;
			while (m_window.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					m_window.close();
				}
			}

			accumulatedTime += m_TickClock.restart().asSeconds();

			

			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal(x,y);
				++x;
				++y;
			}
			if (x == 70)
			{
				x = 0;
				y = 0;
			}
			
		}
	}
	void Application::RenderInternal(int x,int y)
	{
		m_window.clear();

		Render(x,y);

		m_window.display();
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	void Application::Render(int x,int y) // Virtual function can be overriden by the user
	{

		sf::RectangleShape rect{ sf::Vector2f{100,100} };

		rect.setFillColor(sf::Color::Red);
		rect.setOrigin(0,0);
		//rect.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
		rect.setPosition(10*x, 10*y);

		m_window.draw(rect);

	}
	void Application::Tick(float deltaTime) // Virtual function can be overriden by the user
	{
		LOG("The framerate is: %f\n", 1.f / deltaTime);
	}
}