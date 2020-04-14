#define SDL_MAIN_HANDLED  

#include <iostream>
#include "Core/Env/Env.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Utility/Timer.h"
#include "Core/Input/SDL_InputButton.h"
#include "Core/Input/InputButtonHandler.h"
#include "Core/Map/Map.h"
#include "Core/Physic/CollisionHandler.h"

int main()
{
	DonkeyKong::Env env{};
	DonkeyKong::Renderer renderer{};

	if (env && renderer)
	{
		bool exit{ false };

		DonkeyKong::Timer timer{};
        std::unique_ptr<DonkeyKong::InputButtonHandler> inputHandler = std::make_unique<DonkeyKong::SDL_InputButton>();
		DonkeyKong::Map map{renderer};

		while (!exit) 
        {
			timer.Ticks();

            inputHandler->UpdateStatus();

			DonkeyKong::CollisionHandler::CheckCollision();
			map.Update(timer);

			renderer.Color(0, 0, 0, 1);
			renderer.Clear();
			
			map.Draw(renderer);

			renderer.Present();
		}
	}

	return !env;
}
