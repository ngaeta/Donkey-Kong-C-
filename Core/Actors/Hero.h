#pragma once

#include <unordered_map>
#include "../Game_Object/GameObject.h"  
#include "../Utility/Vec2.h"
#include "../FSM/StateMachine.h"

namespace DonkeyKong
{
	class Hero : public GameObject
	{
	public:
		enum class AnimationName { idle, run, jump, climb, die };
		friend class HeroFSMState;

		Hero(const Vec2& pos);
		~Hero() = default;

		void Update(const Timer&) override;
		void OnCollision(const Collider& other, const CollisionInfo info) override;
		void Idle();
		void RunLeft();
		void RunRight();
		void Jump();
		void ClimbUp();
		void ClimbDown();
		void ClimbIdle();
		void Die();
		void SetFallAnim();
		void Win();

		inline const bool& IsGrounded() const { return isGrounded; }
		inline bool& IsGrounded() { return isGrounded; }
		inline const bool& IsDead() const { return isDead; }
		inline const bool& CanClimbFromTop() const { return canClimbFromTop; }
		inline const bool& CanClimbFromDown() const { return canClimbFromDown; }
		inline const bool& HasWon() const { return hasWon; }

	private:
		void CreateAnimation(const AnimationName& name, const int& frames, const int& delay, const Rect& sheetRect);
		void SetCurrAnimation(const AnimationName anim);

		std::shared_ptr<StateMachine> heroFSM;
		std::unordered_map<AnimationName, std::shared_ptr<Animation>> animations;
		AnimationName currAnimName;
		bool canClimbFromTop;
		bool canClimbFromDown;
		bool isGrounded;
		bool isDead;
		bool hasWon;
		const Vec2 moveSpeed;
		const float climbSpeed;
		const int maxYPosDie;
	};
}

