#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class Object
{
	public:
		virtual void Update(sf::Time DeltaTime) = 0;
		virtual void Draw(sf::RenderWindow* Window) = 0;
		virtual ~Object(){};
};