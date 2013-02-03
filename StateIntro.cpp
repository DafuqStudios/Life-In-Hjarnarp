#include "StateIntro.h"
#include "ImageManager.h"
void StateIntro::Init()
{
	VidSprite = new sf::Sprite(*ImageManager::RequestTexture("Assets/Images/Movies/Intro.png"));

	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			TextureRects.push_back(sf::IntRect(i*1280, j*720, 1280, 720));
		}
	}
	VidTiming.restart();
	CurrentFrame = 0;
}

StateIntro::~StateIntro(void)
{
	delete VidSprite;
}

void StateIntro::Update( sf::Time DeltaTime )
{
	if(VidTiming.getElapsedTime().asMilliseconds() > 500)
	{
		VidTiming.restart();
		CurrentFrame++;
		if(CurrentFrame >= TextureRects.size())
			CurrentFrame = 0;
		VidSprite->setTextureRect(TextureRects[CurrentFrame]);
	}
}

void StateIntro::Draw( sf::RenderWindow* Window )
{
	Window->draw(*VidSprite);
}
