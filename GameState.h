#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"
#include <vector>

class GameState : public Object
{
	public:
		virtual void Init() = 0;
		virtual ~GameState(){};

	protected:
		std::vector<Object*> Objects;
};