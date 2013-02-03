#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "GameState.h"
#include "ImageManager.h"

class Engine
{
	public:

		int VID_FLAGS;
		unsigned int DESIRED_FPS;
		sf::Vector2u RESOLUTION;
		std::string WINDOW_TITLE;
		bool bVSYNC;
		static sf::Time DeltaTime;
		static sf::Time TotalDeltaTime;


		void Init();
		void Update();
		void Draw();
		bool Running(){ return m_DisplayWindow.isOpen(); }
		bool Loading(){ return bLoading; }
		void Quit(){ ImageManager::ClearPersistent(); if(m_DisplayWindow.isOpen()) m_DisplayWindow.close(); }
		void SetLoadingState(GameState* State){ m_LoadingState = State; }

		static Engine* GetInstance(){ return &m_Instance; }
		static sf::RenderWindow* GetWindow(){ return &(m_Instance.m_DisplayWindow); }
		static sf::Event* GetEvent(){ return &(m_Instance.EventHandle); }
		static void QueueState(GameState* State){ m_QueuedState = State; }

	private:
		Engine();
		~Engine();
		void ChangeState();
		void ToggleLoading(bool bToggle);
		static void AsyncDraw();
		sf::Thread m_AsyncThread;
		sf::Event EventHandle;

		static bool bLoading;
		static Engine m_Instance;
		static GameState* m_QueuedState;
		GameState* m_CurrentState;
		GameState* m_LoadingState;
		sf::Clock m_DeltaTimer;
		sf::RenderWindow m_DisplayWindow;
};