#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
	class AssetManager //SINGLETON PATTERN
	{
	public:
		
		static AssetManager& Get();
		shared<sf::Texture> LoadTexture(const std::string& path);
		void CleanCyle();

	protected:
		
		AssetManager();

	private:
		
		static unique<AssetManager> m_assetManager;
		Dictionary<std::string, shared<sf::Texture>> m_LoadedTextureMap;
	};
}