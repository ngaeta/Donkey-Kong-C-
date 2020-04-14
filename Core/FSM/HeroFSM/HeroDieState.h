#pragma once

#include "HeroFSM.h"

namespace DonkeyKong
{
	class HeroDieState : public HeroFSMState
	{
	public:
		HeroDieState(Hero& hero);

		// Ereditato tramite HeroFSMState
		void Update(const Timer& t) override;
	};
}