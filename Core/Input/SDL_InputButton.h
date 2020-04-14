#pragma once

#include  <SDL.h>
#include "InputButtonHandler.h"

namespace DonkeyKong
{
	class SDL_InputButton : public InputButtonHandler
	{
	public:
		SDL_InputButton();
		void UpdateStatus() override;

	private:
		const Uint8* keysPressed;
		std::unordered_map<SDL_Keycode, ButtonName> sdl_keycodeMapping;
	};
}