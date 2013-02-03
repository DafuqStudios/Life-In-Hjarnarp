#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <string>


struct TextureObject
{
	public:
		sf::Texture* Texture;
		bool bPersistent;
		std::string Path;
		bool** CData;
		
};

class ImageManager
{
	public:
		static sf::Texture* RequestTexture(std::string Path, bool bSmooth = true, bool bLoadAsTexture = false, bool bPersistent = false);
		static bool** RequestCollisionData(const sf::Texture* Tex);
		static void ClearCache();
		static void ClearPersistent();

	private:

		static std::vector<TextureObject*> Textures;
};