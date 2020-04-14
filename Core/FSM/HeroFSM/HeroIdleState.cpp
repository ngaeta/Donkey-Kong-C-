#include "HeroIdleState.h"
#include "HeroRunState.h"
#include "HeroClimbState.h"
#include "../../Input/InputButtonHandler.h"

namespace DonkeyKong
{
	HeroIdleState::HeroIdleState(Hero& hero) : HeroFSMState(hero)
	{
	}

	void HeroIdleState::Enter()
	{
		hero.Idle();
	}

	void HeroIdleState::Input()
	{
		if (hero.IsGrounded())
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
			else if (InputButtonHandler::IsButtonPressed(ButtonName::Jump))
			{
				machine->SwitchState(static_cast<int>(HeroFSM::HeroState::jump));
			}
			else if (InputButtonHandler::IsButtonPressed(ButtonName::Climb_Up) && hero.CanClimbFromDown())
			{
				HeroClimbState::ClimbButtonPressed = ButtonName::Climb_Up;
				machine->SwitchState(static_cast<int>(HeroFSM::HeroState::climb));
			}
			else if (InputButtonHandler::IsButtonPressed(ButtonName::Climb_Down) && hero.CanClimbFromTop())
			{
				HeroClimbState::ClimbButtonPressed = ButtonName::Climb_Down;
				machine->SwitchState(static_cast<int>(HeroFSM::HeroState::climb));
			}
		}
	}
}
