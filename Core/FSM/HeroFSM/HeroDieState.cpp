#include "HeroDieState.h"

namespace DonkeyKong
{
	HeroDieState::HeroDieState(Hero& hero) : HeroFSMState(hero)
	{
	}

	void HeroDieState::Update(const Timer& t)
	{
		hero.IsGrounded() = false;
	}
}