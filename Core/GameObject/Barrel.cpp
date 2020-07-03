#include "Barrel.h"
#include "../Physic/StandardPhysicsComponent.h"
#include "../Physic/Collider.h"
#include "../Actors/Hero.h"
#include "StaticGameObject.h"
#include <math.h>

namespace DonkeyKong
{
	Barrel::Barrel() : Barrel(Vec2{ 0 })
	{
	}

	Barrel::Barrel(const Vec2 position) : GameObject(position, 17, 14, "Assets/barrel.png"),
		moveSpeed{ 0 }, isBreaked{ false }, rotationSpeedMultiplier {11}
	{
		Tag = "Barrel";

		physicsComponent = std::make_unique<StandardPhysicsComponent>();
		physicsComponent->UseGravity = true;
		colliderPtr = std::make_shared<Collider>(*this, sprite->SpriteRect());

		animations[AnimationName::idle] = std::make_shared<Animation>(1, 50000, Rect{ 0, 0, 17, 14 });
		animations[AnimationName::roll] = std::make_shared<Animation>(1, 3000, Rect{ 0, 22, 16, 11 });
		animations[AnimationName::breaked] = std::make_shared<Animation>(3, 0.5f, Rect{ 0, 38, 21, 17 });
		animations[AnimationName::breaked]->Name = static_cast<int>(AnimationName::breaked);
		animations[AnimationName::breaked]->Loop() = false;

		currAnim = animations[AnimationName::roll];
		currAnim->Play(*sprite);

		velocity = moveSpeed;
	}

	void Barrel::Update(const Timer& timer)
	{
		GameObject::Update(timer);
		rotationSpeed = velocity.x * rotationSpeedMultiplier;

		if (!isGrounded)
		{
			physicsComponent->UseGravity = true;
			physicsComponent->UseAirResistence = true;
		}
		else
			velocity.x = copysignf(moveSpeed.x, velocity.x);

		isGrounded = false;
	}

	void Barrel::OnCollision(const Collider& other, const CollisionInfo info)
	{
		if (typeid(other.Owner()) == typeid(Hero))
		{
			if (!isBreaked)
			{
				Break();
				static_cast<Hero&>(other.Owner()).Die();
			}
		}
		else if (typeid(other.Owner()) == typeid(StaticGameObject) && other.ColliderRect().y > Position().y)
		{
			if (!isGrounded)
			{
				velocity.y = 0;
				isGrounded = true;
				physicsComponent->UseGravity = false;
				physicsComponent->UseAirResistence = false;
				if (isBreaked) velocity.x = 0;
			}

			if (!isBreaked)
			{
				if (other.Owner().Rotation() != 0)
				{
					velocity.x = copysignf(velocity.x, other.Owner().Rotation());
					rotationSpeed = copysignf(rotationSpeed, other.Owner().Rotation());
				}
			}

			Position().y += -info.Delta.y;;
		}
	}

	void Barrel::Roll(const Vec2& newPos, const Vec2& newSpeed)
	{
		Position() = newPos;
		moveSpeed = newSpeed;
		velocity = moveSpeed;
		isBreaked = false;
		currAnim = animations[AnimationName::roll];
		currAnim->Play(*sprite);
	}

	const bool Barrel::IsBreakAnimFinished() const
	{
		return currAnim->Name == static_cast<int>(AnimationName::breaked) && !currAnim->IsPlaying();
	}

	void Barrel::Break()
	{
		if (!isBreaked)
		{
			if (isGrounded)
			{
				velocity.x = 0;
			}
			else
			{
				velocity.y *= 0.2f;
				velocity.x *= 0.2f;
			}

			isBreaked = true;
			rotationSpeed = 0;
			currAnim = animations[AnimationName::breaked];
			currAnim->Play(*sprite);
		}
	}
}
