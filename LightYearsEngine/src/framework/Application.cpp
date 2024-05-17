#include "framework/Application.h"
#include <framework/Core.h>
#include <framework/World.h>
#include "framework/AssetManager.h"

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: m_window{ sf::VideoMode(windowWidth,windowHeight),title, style },
		m_TargetFrameRate{ 144.f },
		m_TickClock{},
		m_currentWorld{ nullptr },
		m_CleanCycleClock{},
		m_CleanCycleInterval{ 2.f }

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
				TickInternal(targetDeltaTime); //TICKING
				RenderInternal(); //RENDERING
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

		if (m_currentWorld)
		{
			m_currentWorld->TickInternal(deltaTime);
		}

		if (m_CleanCycleClock.getElapsedTime().asSeconds() >= m_CleanCycleInterval)
		{
			m_CleanCycleClock.restart();
			AssetManager::Get().CleanCyle();
		}
	}

	void Application::Render() // Virtual function can be overriden by the user
	{
		if (m_currentWorld)
		{
			m_currentWorld->Render(m_window);
		}

	}

	void Application::Tick(float deltaTime) // Virtual function can be overriden by the user
	{
		
	}
}