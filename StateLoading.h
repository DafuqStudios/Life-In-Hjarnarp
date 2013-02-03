#pragma once
#include "gamestate.h"

class StateLoading :
	public GameState
{
	public:
		~StateLoading(void);
		virtual void Init() override;
		virtual void Update(sf::Time DeltaTime) override;
		virtual void Draw(sf::RenderWindow* Window) override;

	private:
		sf::Sprite* m_BackgroundImg;
		sf::Font* m_BlipsFont;
		sf::Text* m_LoadingTextBlips;
};

