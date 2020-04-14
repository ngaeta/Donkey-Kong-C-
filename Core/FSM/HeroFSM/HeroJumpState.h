#pragma once

#include "HeroFSM.h"

namespace DonkeyKong
{
	class HeroJumpState : public HeroFSMState
	{
	public:
		HeroJumpState(Hero& hero) : HeroFSMState(hero) {}
		// Ereditato tramite HeroFSMState
		virtual void Enter() override;
		virtual void Input() override;
		virtual void Update(const Timer& t) override;
	};
}

