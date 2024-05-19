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
		void setAssetRootDirectory(const std::string& directory);

	protected:
		AssetManager();
	private:
		
		static unique<AssetManager> m_assetManager;
		Dictionary<std::string, shared<sf::Texture>> m_LoadedTextureMap;
		std::string m_rootDirectory;
	};
}