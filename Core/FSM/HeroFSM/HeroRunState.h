#pragma once

#include "HeroFSM.h"
#include "../../Input/InputButtonHandler.h"

namespace DonkeyKong
{
	class HeroRunState : public HeroFSMState
	{
	public:
		HeroRunState() = delete;
		HeroRunState(Hero& hero) : HeroFSMState(hero) {}

		void Enter() override;
		void Input() override;

		static ButtonName ButtonRunPressed;
	};
}
