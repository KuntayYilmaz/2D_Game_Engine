#include "framework/Application.h"
#include <iostream>

namespace ly
{
	Application::Application()
		: m_window{ sf::VideoMode(1000,1000),"Light Years" },
		m_TargetFrameRate{144.f},
		m_TickClock{}
	{
			
	}
	void Application::Run()
	{
		m_TickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / m_TargetFrameRate;
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
				Tick(targetDeltaTime);

			}
		}
	}
	void Application::Render()
	{
		
	}
	void Application::Tick(float deltaTime)
	{
		std::cout << "The framerate is: " <<  1.f / deltaTime << std::endl;
	}
}