#pragma once
#include "gamestate.h"
#include <vector>
#include <SFML/Graphics.hpp>
class StateIntro :
	public GameState
{
	public:
		~StateIntro(void);
		virtual void Init() override;
		virtual void Update(sf::Time DeltaTime) override;
		virtual void Draw(sf::RenderWindow* Window) override;

	private:
		std::vector<sf::IntRect> TextureRects;
		sf::Sprite* VidSprite;
		sf::Clock VidTiming;
		int CurrentFrame;
};

