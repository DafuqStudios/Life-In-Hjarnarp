#include "ImageManager.h"

#include <iostream>
#include <string>
#include "Utility.h"

std::vector<TextureObject*> ImageManager::Textures;

bool** ImageManager::RequestCollisionData(const sf::Texture* Tex)
{
	for(unsigned int i = 0; i < Textures.size(); i++)
	{
		if(Textures[i]->Texture == Tex)
		{
			return Textures[i]->CData;
		}
	}
	return nullptr;
}

sf::Texture* ImageManager::RequestTexture(std::string Path, bool bSmooth, bool bLoadAsTexture, bool bPersistent)
{
	for(unsigned int i = 0; i < Textures.size(); i++)
	{
		if(Textures[i]->Path == Path)
		{
			return Textures[i]->Texture;
		}
	}
	

	TextureObject* TexObj = new TextureObject();
	sf::Image* Img = new sf::Image();
	sf::Texture* Tex = new sf::Texture();
	bool** tempsize;
	if(!bLoadAsTexture)
	{
		if(Img->loadFromFile(Path))
		{
			bool** CD = new bool *[Img->getSize().x];
			tempsize = CD;	
			Util::msgNote(Util::BuildString("New image loaded: %s", Path.c_str()));
			for (int x = 0; x < Img->getSize().x; x++)
			{
				CD[x] = new bool[Img->getSize().y];
			}
		}
		else
		{
			Util::msgErr(Util::BuildString("Error loading image: %s", Path.c_str()));
			return nullptr;
		}

		for(int x = 0; x < Img->getSize().x; x++)
		{
			for(int y = 0; y < Img->getSize().y; y++)
			{
				if (Img->getPixel(x, y).a < 50)
				{
					tempsize[x][y] = false;
				} else {
					tempsize[x][y] = true;
				}
			}
		}
		Tex->loadFromImage(*Img);
		TexObj->CData = tempsize;
	}
	else
	{
		Tex->loadFromFile(Path);
		TexObj->CData = nullptr;
	}

	Tex->setSmooth(bSmooth);
	TexObj->Texture = Tex;
	TexObj->bPersistent = bPersistent;
	TexObj->Path = Path;
	Textures.push_back(TexObj);

	
	delete Img;
	return Tex;
}

void ImageManager::ClearCache()
{
	for(unsigned int i = 0; i < Textures.size(); i++)
	{
		if(!Textures[i]->bPersistent)
		{
			delete Textures[i]->Texture;
			delete Textures[i];
			Textures.erase(Textures.begin() + i);
		}
	}
}

void ImageManager::ClearPersistent()
{
	for(unsigned int i = 0; i < Textures.size(); i++)
	{
		delete Textures[i]->Texture;
		delete Textures[i];
	}
	Textures.clear();
}