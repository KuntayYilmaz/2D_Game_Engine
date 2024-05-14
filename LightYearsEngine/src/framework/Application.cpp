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
				RenderInternal();
			}
			
		}
	}
	void Application::RenderInternal()
	{
		m_window.clear();

		Render();

		m_window.display();
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	void Application::Render() // Virtual function can be overriden by the user
	{

		sf::RectangleShape rect{ sf::Vector2f{100,100} };

		rect.setFillColor(sf::Color::Red);
		rect.setOrigin(50, 50);
		rect.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);

		m_window.draw(rect);

	}
	void Application::Tick(float deltaTime) // Virtual function can be overriden by the user
	{
		LOG("The framerate is: %f\n", 1.f / deltaTime);
	}
}