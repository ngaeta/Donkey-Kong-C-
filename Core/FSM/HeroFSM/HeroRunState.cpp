#include "HeroRunState.h"

namespace DonkeyKong
{
	ButtonName HeroRunState::ButtonRunPressed = ButtonName::Move_Left;

	void HeroRunState::Enter()
	{
		ButtonRunPressed == ButtonName::Move_Left ? hero.RunLeft() : hero.RunRight();
	}

	void HeroRunState::Input()
	{
		if (hero.IsGrounded())
		{
			if (!InputButtonHandler::IsButtonPressed(ButtonRunPressed))
			{
				machine->SwitchState(static_cast<int>(HeroFSM::HeroState::idle));
				return;
			}

			if (InputButtonHandler::IsButtonPressed(ButtonName::Jump))
			{
				machine->SwitchState(static_cast<int>(HeroFSM::HeroState::jump));
			}
		}
	}
}
