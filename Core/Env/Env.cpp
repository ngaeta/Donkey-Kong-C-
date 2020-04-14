#include "SDL.h"
#include "Env.h"

namespace DonkeyKong
{
	Env::Env() : init{}
	{
		init = (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) == 0);
	}

	Env::~Env()
	{
		if (init)
		{
			SDL_Quit();
		}
	}

	Env::operator bool()
	{
		return init;
	}
}
