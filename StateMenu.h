#pragma once
#include "gamestate.h"

class StateMenu :
	public GameState
{
	public:
		~StateMenu(void);
		virtual void Init() override;
		virtual void Update(sf::Time DeltaTime) override;
		virtual void Draw(sf::RenderWindow* Window) override;

	private:
		sf::Sprite* m_Background;
};

