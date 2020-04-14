#pragma once

#include "HeroFSM.h"

namespace DonkeyKong
{
	class HeroIdleState : public HeroFSMState
	{
	public:
		HeroIdleState(Hero& hero);

		// Ereditato tramite HeroFSMState
		void Enter() override;
		void Input() override;
	};
}

