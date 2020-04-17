#include "Hero.h"
#include "../Utility/Vec2.h"
#include "../Sprite/Animation.h"
#include "../Physic/Collider.h"
#include "../Physic/StandardPhysicsComponent.h"
#include "../Game_Object/StaticGameObject.h"
#include "../Game_Object/Ladder.h"
#include "../FSM/HeroFSM/HeroFSM.h"
#include <SDL.h>

namespace DonkeyKong
{
	Hero::Hero(const Vec2& pos) : GameObject(pos, 20, 18, "assets/mario_sheet.png"),
		moveSpeed{ 100, 100 }, climbSpeed{ 30.0 }, 
		isGrounded{ false }, isDead{ false }, canClimbFromDown{ false }, canClimbFromTop{ false }, hasWon{false}, 
		maxYPosDie { Renderer::WindowHeight - static_cast<int>(sprite->SpriteRect().h * 0.5) }
	{
		Tag = "Hero";

		heroFSM = std::make_shared<HeroFSM>(*this);
		Rect spriteRect = sprite->SpriteRect();
		collider_ptr = std::make_shared<Collider>(*this, Rect{ spriteRect.x, spriteRect.y, spriteRect.w, spriteRect.h });
		physics_component = std::make_unique<StandardPhysicsComponent>();
		physics_component->UseGravity = false;

		CreateAnimation(AnimationName::idle, 1, 100000, Rect{ 0, 0, 20, 18});
		CreateAnimation(AnimationName::run, 2, 100, Rect{ 0, 0, 20, 18});
		CreateAnimation(AnimationName::jump, 1, 100000, Rect{ 60, 0, 20, 18});
		CreateAnimation(AnimationName::climb, 2, 200, Rect{ 0, 46, 19, 19});
		CreateAnimation(AnimationName::die, 4, 250, Rect{ 0, 22, 23, 18, });
		animations[AnimationName::die]->Loop() = false;

		SetCurrAnimation(AnimationName::idle);
	}

	void Hero::Update(const Timer& t)
	{
		if (!hasWon) heroFSM->Input();

		GameObject::Update(t);
		heroFSM->Update(t);		
	}

	void Hero::OnCollision(const Collider& other, const CollisionInfo collisionInfo)
	{
		heroFSM->OnCollision(other, collisionInfo);
	}

	void Hero::Idle()
	{
		if (isGrounded && currAnimName != AnimationName::idle)
		{
			canClimbFromDown = canClimbFromTop = false;
			velocity.x = velocity.y = 0;
			SetCurrAnimation(AnimationName::idle);
		}
	}

	void Hero::RunLeft()
	{
		if (velocity.x >= 0)
		{
			velocity.x = -moveSpeed.x;
			sprite->FlipX(true);
		}

		if (isGrounded && currAnimName != AnimationName::run)
		{
			SetCurrAnimation(AnimationName::run);
		}
	}

	void Hero::RunRight()
	{
		if (velocity.x <= 0)
		{
			velocity.x = moveSpeed.x;
			sprite->FlipX(false);
		}

		if (isGrounded && currAnimName != AnimationName::run)
		{
			SetCurrAnimation(AnimationName::run);
		}
	}

	void Hero::Jump()
	{
		if (isGrounded)
		{
			isGrounded = false;
			physics_component->UseGravity = true;
			velocity.y = -moveSpeed.y;
			SetCurrAnimation(AnimationName::jump);
		}
	}

	void Hero::ClimbUp()
	{
		if (velocity.y >= 0)
		{
			isGrounded = false;
			physics_component->UseGravity = false;
			velocity.y = -climbSpeed;
			animations[AnimationName::climb]->SetReversed(false);
			SetCurrAnimation(AnimationName::climb);
		}
	}

	void Hero::ClimbDown()
	{
		if (velocity.y <= 0)
		{
			isGrounded = false;
			physics_component->UseGravity = false;
			velocity.y = climbSpeed;
			animations[AnimationName::climb]->SetReversed(true);
			SetCurrAnimation(AnimationName::climb);
		}
	}

	void Hero::ClimbIdle()
	{
		if (currAnimName == AnimationName::climb && curr_animation->IsPlaying())
		{
			curr_animation->Pause();
			velocity.y = 0;
		}
	}

	void Hero::Die()
	{
		if (!isDead)
		{
			velocity.x = 0;

			if (isGrounded)
			{
				velocity.y = 0;
			}
			else
				physics_component->UseGravity = true;

			isDead = true;
			canClimbFromTop = canClimbFromDown = false;
			SetCurrAnimation(AnimationName::die);
			heroFSM->SwitchState(static_cast<int>(HeroFSM::HeroState::die));		
		}
	}

	void Hero::SetFallAnim()
	{
		isGrounded = false;
		physics_component->UseGravity = true;
		SetCurrAnimation(AnimationName::jump);
	}

	void Hero::Win()
	{
		if (!hasWon)
		{
			std::cout << "WIN" << std::endl;
			hasWon = true;
			velocity.x = 0;
			if(isGrounded) heroFSM->SwitchState(static_cast<int>(HeroFSM::HeroState::idle));
		}
	}

	void Hero::CreateAnimation(const AnimationName& name, const int& frames, const int& delay, const Rect& sheetRect)
	{
		animations[name] = std::make_shared<Animation>(frames, delay, sheetRect);
		animations[name]->Name = static_cast<int>(name);
	}

	void Hero::SetCurrAnimation(const AnimationName anim)
	{
		currAnimName = anim;
		curr_animation = animations[anim];
		curr_animation->Play(*sprite);
	}
}
