#pragma once

#include "Engine.h"
#include "StateLoading.h"
#include "StateIntro.h"
int main(int argc, char *argv[])
{
	Engine* EngineInstance = Engine::GetInstance();
	EngineInstance->WINDOW_TITLE = "Life in Hjärnarp";
	EngineInstance->RESOLUTION = sf::Vector2u(1280, 720);
	//EngineInstance->VID_FLAGS = sf::Style::Fullscreen;
	EngineInstance->SetLoadingState(new StateLoading);
	EngineInstance->Init();

	EngineInstance->QueueState(new StateIntro);

	while(EngineInstance->Running())
	{
		EngineInstance->Update();
		EngineInstance->Draw();
	}

	return 0;
}