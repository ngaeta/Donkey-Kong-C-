#pragma once

#include "../State.h"
#include "../StateMachine.h"
#include "../../Actors/Hero.h"
#include "../../Physic/Collider.h"

namespace DonkeyKong
{
	class HeroFSM : public StateMachine
	{
	public:
		enum class HeroState { idle, run, jump, climb, falling, die };

		HeroFSM(Hero& hero);
	};

	class HeroFSMState : public State
	{
	public:
		HeroFSMState(Hero& _hero);

		void OnCollision(const Collider& other, const CollisionInfo collisionInfo) override final;

		virtual void Update(const Timer& t) override;
		virtual void Enter() override;
		virtual void Input() override;
		virtual void Exit() override;

	protected:
		virtual void OnCollisionFromTop(const Collider& other, const CollisionInfo collisionInfo);
		virtual void OnCollisionFromBottom(const Collider& other, const CollisionInfo collisionInfo);

		const bool CheckIfOutOfScreen() const;

		Hero& hero; 
	};
}
