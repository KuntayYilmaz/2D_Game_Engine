#include "framework/AssetManager.h"
#include "framework/Core.h"

namespace ly
{
	unique<AssetManager> AssetManager::m_assetManager{ nullptr };

	AssetManager& AssetManager::Get()
	{
		if (!m_assetManager)
		{
			m_assetManager = std::move(unique<AssetManager>{new AssetManager});
		}

		return *m_assetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		auto found = m_LoadedTextureMap.find(path);
		if (found != m_LoadedTextureMap.end()) // CHECH IF TEXTURE ALREADY LOADED INTO GAME
		{
			return found->second;
		}

		shared<sf::Texture> newTexture{ new sf::Texture };

		if (newTexture->loadFromFile(path)) //CHECK IF NEW TEXTURE LOADED PROPERLY
		{
			m_LoadedTextureMap.insert({ path, newTexture });
			return newTexture;
		}

		return shared<sf::Texture> {nullptr}; //IF FAILED
	}

	void AssetManager::CleanCyle()
	{
		

		for (auto it = m_LoadedTextureMap.begin(); it != m_LoadedTextureMap.end();)
		{
			if (it->second.unique())
			{
				LOG("Cleaning Texture: %s", it->first.c_str());
				it = m_LoadedTextureMap.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	AssetManager::AssetManager()
	{

	}
}