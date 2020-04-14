#ifndef AIV_TIMER
#define AIV_TIMER

#include <SDL.h>

namespace DonkeyKong
{
	class Timer
	{
	public:
		Timer();
		~Timer() = default;

		void Ticks();
		const Uint32 Wall() const;
		inline const double& DeltaTime() const { return deltaTime; }

	private:
		Uint64 last;
		Uint64 now;
		double deltaTime;
	};
}


#endif
