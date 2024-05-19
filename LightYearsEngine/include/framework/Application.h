#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"


namespace ly
{
	class World;
	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

		sf::Vector2u GetWindowSize() const;

	private:
		void RenderInternal();
		void TickInternal(float deltaTime);
		
		virtual void Render();
		virtual void Tick(float deltaTime);

		//VARIABLES
		sf::RenderWindow m_window;
		float m_TargetFrameRate;
		sf::Clock m_TickClock;

		shared<World> m_currentWorld;
		sf::Clock m_CleanCycleClock;
		float m_CleanCycleInterval;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		m_currentWorld = newWorld;
		m_currentWorld->BeginPlayInternal();
		return newWorld;
	}
}