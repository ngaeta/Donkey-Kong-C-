#include "HeroClimbState.h"
#include "../../GameObject/StaticGameObject.h"

namespace DonkeyKong
{
	ButtonName HeroClimbState::ClimbButtonPressed = ButtonName::Climb_Up;
	ButtonName HeroClimbState::ClimbButtonToCheck = ButtonName::Climb_Down;

	HeroClimbState::HeroClimbState(Hero& hero) : HeroFSMState(hero)
	{
	}

	void HeroClimbState::Enter()
	{
		if (ClimbButtonPressed == ButtonName::Climb_Up)
		{
			hero.ClimbUp();
			ClimbButtonToCheck = ButtonName::Climb_Down;
		}
		else
		{
			hero.ClimbDown();
			ClimbButtonToCheck = ButtonName::Climb_Up;
		}
	}

	void HeroClimbState::Input()
	{
		if (InputButtonHandler::IsButtonPressed(ClimbButtonPressed))
		{
			if(!hero.IsGrounded())
				machine->SwitchState(static_cast<int>(HeroFSM::HeroState::climb));
		}
		else if (InputButtonHandler::IsButtonPressed(ClimbButtonToCheck))
		{
			ClimbButtonPressed = ClimbButtonToCheck;
			machine->SwitchState(static_cast<int>(HeroFSM::HeroState::climb));
		}
		else
		{
			hero.ClimbIdle();
		}
	}

	void HeroClimbState::Update(const Timer& t)
	{
		if (CheckIfOutOfScreen())
		{
			return;
		}

		if (!hero.IsDead())
		{
			if (hero.IsGrounded())
			{
				machine->SwitchState(static_cast<int>(HeroFSM::HeroState::idle));
			}
		}
	}

	void HeroClimbState::OnCollisionFromTop(const Collider& other, const CollisionInfo collisionInfo)
	{
		//std::cout << "Collision with delta: " << collisionInfo.Delta.y << std::endl;
		if (!hero.IsGrounded() && typeid(other.Owner()) == typeid(StaticGameObject) && collisionInfo.Delta.y < 0)
		{
			hero.IsGrounded() = true;
		}
	}

	void HeroClimbState::OnCollisionFromBottom(const Collider& other, const CollisionInfo collisionInfo)
	{
		//std::cout << "From bottom" << std::endl;		
	}
}
