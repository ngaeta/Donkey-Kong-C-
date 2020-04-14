#pragma once

#include "HeroFSM.h"

namespace DonkeyKong
{
	class HeroFallingState : public HeroFSMState
	{
	public:
		HeroFallingState(Hero& hero) : HeroFSMState(hero){}

		void Enter() override;
		void Input() override;
		void Update(const Timer& t) override;
	};
}

