#include "Engine.h"
#include "Utility.h"
#include <iostream>
#include <ctime>
#include <typeinfo>

static const float VERSION = 1.0f;
static const float SUB_VERSION = 0.0f;

Engine Engine::m_Instance;
GameState* Engine::m_QueuedState;
bool Engine::bLoading;
sf::Time Engine::DeltaTime;
sf::Time Engine::TotalDeltaTime;

Engine::Engine() : m_AsyncThread(&AsyncDraw)
{
	/* Defaults */
	srand((unsigned int)time(NULL));
	VID_FLAGS = sf::Style::Default;
	DESIRED_FPS = 60;
	RESOLUTION = sf::Vector2u(800, 600);
	WINDOW_TITLE = "Phoenix Engine";
	bVSYNC = false;
	DeltaTime = sf::milliseconds(0);

	m_CurrentState = nullptr;
	m_QueuedState = nullptr;
	m_LoadingState = nullptr;
}

Engine::~Engine()
{
	if(m_CurrentState != nullptr)
		delete m_CurrentState;
	if(m_QueuedState != nullptr)
		delete m_QueuedState;
	if(m_LoadingState != nullptr)
		delete m_LoadingState;
}

void Engine::Init()
{
	/* ASCII art + Version print */
	std::vector<std::string> ASCII_Sequence;
	std::vector<CON_COLOR> Color_Sequence;
	ASCII_Sequence.push_back("                            _____ _____ _      _____ ");
	ASCII_Sequence.push_back("                           |_   _|_   _| |    |  ___|");
	ASCII_Sequence.push_back("__   _____ _ __ ___  __ _    | |   | | | |    | |__  ");
	ASCII_Sequence.push_back("\\ \\ / / _ \\ '__/ __|/ _` |   | |   | | | |    |  __| ");
	ASCII_Sequence.push_back(" \\ V /  __/ |  \\__ \\ (_| |   | |  _| |_| |____| |___ ");
	ASCII_Sequence.push_back("  \\_/ \\___|_|  |___/\\__,_|   \\_/  \\___/\\_____/\\____/ ");
	Color_Sequence.push_back(LIGHTBLUE);
	Color_Sequence.push_back(LIGHTBLUE);
	Color_Sequence.push_back(LIGHTBLUE);
	Color_Sequence.push_back(LIGHTAQUA);
	Color_Sequence.push_back(LIGHTAQUA);
	Color_Sequence.push_back(LIGHTBLUE);

	for(unsigned int i = 0; i < ASCII_Sequence.size(); i++)
		Util::PrintColor(Util::BuildString("%s\n", ASCII_Sequence[i].c_str()), Color_Sequence[i]);
	Util::PrintColor("\nVersaTILE engine [ ", GREEN);
	Util::PrintColor(Util::BuildString("version %1.1f.%1.1f", VERSION, SUB_VERSION), LIGHTGREEN);
	Util::PrintColor(" ]\n\n\n", GREEN);

	/* System init */
	Util::msgStd("Starting Engine...");

	m_DisplayWindow.create(sf::VideoMode(RESOLUTION.x, RESOLUTION.y), WINDOW_TITLE, VID_FLAGS);

	if(!bVSYNC)
		if(DESIRED_FPS > 0)
			m_DisplayWindow.setFramerateLimit(DESIRED_FPS);
	else
		m_DisplayWindow.setVerticalSyncEnabled(true);

	if(m_LoadingState != nullptr)
		m_LoadingState->Init();
	else
		Util::msgWarn("No LoadingState set; Screen will be black while loading.");
}

void Engine::ChangeState()
{
	if(m_QueuedState == m_LoadingState)
	{
		m_CurrentState = m_LoadingState;
		return;
	}

	Util::PrintColor("Entering State ", WHITE);
	Util::PrintColor(Util::BuildString("%s\n", typeid(*m_QueuedState).name()), GREEN);

	if(m_QueuedState != nullptr)
	{
		if(m_CurrentState != nullptr)
		{
			delete m_CurrentState;
			m_CurrentState = nullptr;
			ImageManager::ClearCache();
		}

		GameState* TemporaryState = m_QueuedState;
		ToggleLoading(true);
		TemporaryState->Init();
		ToggleLoading(false);
		m_CurrentState = TemporaryState;


		m_QueuedState = nullptr;
	}
}

void Engine::ToggleLoading(bool bToggle)
{
	sf::Context Cont;
	if(m_LoadingState != nullptr)
	{
		if(bToggle)
		{
			bLoading = true;
			m_QueuedState = m_LoadingState;
			ChangeState();
			m_DisplayWindow.setActive(false); //Give thread access to window context
			m_AsyncThread.launch();
		}
		else
		{
			bLoading = false;
			m_AsyncThread.wait();
			m_DisplayWindow.setActive(true);
		}
	}
}

void Engine::Update()
{
	DeltaTime = m_DeltaTimer.restart();
	TotalDeltaTime += DeltaTime;

	if(m_QueuedState != nullptr)
		ChangeState();

	while(m_DisplayWindow.pollEvent(EventHandle))
	{
		if(EventHandle.type == sf::Event::KeyPressed && EventHandle.key.code == sf::Keyboard::Return && EventHandle.key.alt)
		{
			VID_FLAGS ^= sf::Style::Fullscreen;
			m_DisplayWindow.create(sf::VideoMode(RESOLUTION.x, RESOLUTION.y), WINDOW_TITLE, VID_FLAGS);
		}

		if (EventHandle.type == sf::Event::Closed)
			Quit();
	}

	if(m_CurrentState != nullptr)
		m_CurrentState->Update(DeltaTime);
}

void Engine::Draw()
{
	m_DisplayWindow.clear();

	if(m_CurrentState != nullptr)
		m_CurrentState->Draw(&m_DisplayWindow);

	m_DisplayWindow.display();
}

void Engine::AsyncDraw()
{
	while(Engine::GetInstance()->Loading())
	{
		Engine::GetInstance()->Update();
		Engine::GetInstance()->Draw();
	}
}