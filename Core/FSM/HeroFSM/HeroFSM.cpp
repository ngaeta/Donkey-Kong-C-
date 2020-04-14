#include "HeroFSM.h"
#include "HeroIdleState.h"
#include "HeroRunState.h"
#include "HeroJumpState.h"
#include "HeroClimbState.h"
#include "HeroFallingState.h"
#include "HeroDieState.h"
#include "../../Game_Object/Ladder.h"
#include "../../Game_Object/StaticGameObject.h"
#include "../../Actors/Lady.h"

namespace DonkeyKong
{
	HeroFSM::HeroFSM(Hero& hero) : StateMachine(hero)
	{
		RegisterState(static_cast<int>(HeroState::idle), std::make_shared<HeroIdleState>(hero));
		RegisterState(static_cast<int>(HeroState::run), std::make_shared<HeroRunState>(hero));
		RegisterState(static_cast<int>(HeroState::jump), std::make_shared<HeroJumpState>(hero));
		RegisterState(static_cast<int>(HeroState::climb), std::make_shared<HeroClimbState>(hero));
		RegisterState(static_cast<int>(HeroState::falling), std::make_shared<HeroFallingState>(hero));
		RegisterState(static_cast<int>(HeroState::die), std::make_shared<HeroDieState>(hero));

		SwitchState(static_cast<int>(HeroState::idle));
	}

	HeroFSMState::HeroFSMState(Hero& _hero) : State(), hero{ _hero }
	{
	}

	void HeroFSMState::Update(const Timer& t)
	{
		if (CheckIfOutOfScreen())
		{
			return;
		}

		if (!hero.IsGrounded())
		{
			machine->SwitchState(static_cast<int>(HeroFSM::HeroState::falling));
		}

		hero.IsGrounded() = false;
		hero.canClimbFromTop = hero.canClimbFromDown = false;
	}

	void HeroFSMState::Enter()
	{
	}

	void HeroFSMState::Input()
	{
	}

	void HeroFSMState::OnCollision(const Collider& other, const CollisionInfo collisionInfo)
	{
		if (typeid(other.Owner()) == typeid(Lady))
		{
			hero.Win();
			static_cast<Lady&>(other.Owner()).SetLoveAnimation();
			return;
		}

		float deltaX = collisionInfo.Delta.x;
		float deltaY = collisionInfo.Delta.y;

		//if (typeid(other.Owner()) == typeid(Ladder))
		//{
		//	std::cout << "Delta x: " << deltaX << std::endl;
		//	std::cout << "Delta y: " << deltaY << std::endl;
		//}

		if (deltaX >= deltaY)
		{
			//collision from top or bottom
			if (hero.Position().y < other.ColliderRect().y)
			{

				OnCollisionFromTop(other, collisionInfo);
			}
			else
			{
				OnCollisionFromBottom(other, collisionInfo);
			}
		}
		else
		{		
			//std::cout << "Collision from Right or left" << std::endl;
			//if delta e poco, togliere canformbottom 

			//collision from right or left

			//if (Position().x < other.ColliderRect().x)
			//{
			//	//from letf
			//	deltaX = -deltaX;
			//}
			///*if(!isGrounded)
			//	velocity.x = 0;*/
			//	//Position() = Vec2{ Position().x + deltaX, Position().y };
		}
	}

	void HeroFSMState::Exit()
	{
	}

	void HeroFSMState::OnCollisionFromTop(const Collider& other, const CollisionInfo collisionInfo)
	{
		if (!hero.canClimbFromTop)
		{
			hero.canClimbFromTop = typeid(other.Owner()) == typeid(Ladder) && collisionInfo.Delta.x > 10;
		}

		if (!hero.isGrounded && typeid(other.Owner()) == typeid(StaticGameObject))
		{
			if (hero.velocity.y >= 0)
			{
				hero.isGrounded = true;
				hero.velocity.y = 0;
				hero.physics_component->UseGravity = false;
				hero.Position().y += -collisionInfo.Delta.y;;
			}
		}
	}

	void HeroFSMState::OnCollisionFromBottom(const Collider& other, const CollisionInfo collisionInfo)
	{
		if (!hero.canClimbFromDown)
			hero.canClimbFromDown = typeid(other.Owner()) == typeid(Ladder) && collisionInfo.Delta.x > 10;

		if (hero.velocity.y < 0)
		{
			hero.velocity.y = -hero.velocity.y;
		}
	}

	const bool HeroFSMState::CheckIfOutOfScreen() const
	{
		if (hero.isDead)
			return true;

		if (hero.Position().y > hero.minYPosToDead)
		{
			hero.velocity.y = -hero.speed.y;
			hero.Die();
			return true;
		}

		return false;
	}
}
