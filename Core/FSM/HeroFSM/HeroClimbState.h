#pragma once

#include "HeroFSM.h"
#include "../../Input/InputButtonHandler.h"

namespace DonkeyKong
{
	class HeroClimbState : public HeroFSMState
	{
	public:
		HeroClimbState(Hero& hero);

		// Ereditato tramite HeroFSMState
		void Enter() override;
		void Input() override;
		void Update(const Timer& t) override;
		void OnCollisionFromTop(const Collider& other, const CollisionInfo collisionInfo) override;
		void OnCollisionFromBottom(const Collider& other, const CollisionInfo collisionInfo) override;

		static ButtonName ClimbButtonPressed;

	private:
		static ButtonName ClimbButtonToCheck;
	};
}
