#include <SDL_timer.h>
#include "Timer.h"

namespace DonkeyKong 
{
	Timer::Timer() : now{ SDL_GetPerformanceCounter() }, last {}, deltaTime{}
    {
    }

    void Timer::Ticks()  
    {
		last = now;
		now = SDL_GetPerformanceCounter();

		deltaTime = ((double)((now - last) * 1000) / SDL_GetPerformanceFrequency()) * 0.001;
    }

    const Uint32 Timer::Wall() const 
    {
        return SDL_GetTicks();
    }
}
