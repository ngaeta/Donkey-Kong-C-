#include "HeroJumpState.h"
#include "HeroRunState.h"
#include "../../Input/InputButtonHandler.h"

namespace DonkeyKong
{
	void HeroJumpState::Enter()
	{
		hero.Jump();
	}

	void HeroJumpState::Input()
	{
		if (!hero.IsGrounded())
		{
			if (InputButtonHandler::IsButtonPressed(ButtonName::Move_Left))
			{
				HeroRunState::ButtonRunPressed = ButtonName::Move_Left;
				machine->SwitchState(static_cast<int>(HeroFSM::HeroState::run));
			}
			else if (InputButtonHandler::IsButtonPressed(ButtonName::Move_Right))
			{
				HeroRunState::ButtonRunPressed = ButtonName::Move_Right;
				machine->SwitchState(static_cast<int>(HeroFSM::HeroState::run));
			}
		}
	}

	void HeroJumpState::Update(const Timer& t)
	{
		if (CheckIfOutOfScreen())
		{
			return;
		}

		if (hero.IsGrounded() && !hero.IsDead())
		{
			machine->SwitchState(static_cast<int>(HeroFSM::HeroState::idle));
		}
	}
}