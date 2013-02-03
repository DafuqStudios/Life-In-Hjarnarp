#include "StateMenu.h"
#include "ImageManager.h"

void StateMenu::Init()
{
	m_Background = new sf::Sprite(*ImageManager::RequestTexture("Assets/Images/Backgrounds/Menu.png"));
}

StateMenu::~StateMenu(void)
{
	delete m_Background;
}

void StateMenu::Update( sf::Time DeltaTime )
{

}

void StateMenu::Draw( sf::RenderWindow* Window )
{
	Window->draw(*m_Background);
}
