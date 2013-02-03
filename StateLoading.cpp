#include "StateLoading.h"
#include "ImageManager.h"
#include "Engine.h"
#include "Utility.h"

void StateLoading::Init()
{
	m_BackgroundImg = new sf::Sprite(*ImageManager::RequestTexture("Assets/Images/Backgrounds/Loading.png"));
	m_BlipsFont = new sf::Font();
	m_BlipsFont->loadFromFile("Assets/Fonts/Minecraftia.ttf");
	m_LoadingTextBlips = new sf::Text(".", *m_BlipsFont, 100);
	m_LoadingTextBlips->setColor(sf::Color::White);
}

StateLoading::~StateLoading(void)
{
	delete m_BackgroundImg;
	delete m_LoadingTextBlips;
	delete m_BlipsFont;
}

void StateLoading::Update(sf::Time DeltaTime)
{
	sf::String newTxt = "";
	for(int i = 0; i < ((int)(Engine::TotalDeltaTime.asMilliseconds()/500)%11); i++)
		newTxt += ".";
	m_LoadingTextBlips->setString(newTxt);
}

void StateLoading::Draw(sf::RenderWindow* Window)
{
	m_LoadingTextBlips->setPosition( Util::CenterText(m_LoadingTextBlips, Window) );
	m_LoadingTextBlips->move(0, 20);
	Window->draw(*m_BackgroundImg);
	Window->draw(*m_LoadingTextBlips);
}
