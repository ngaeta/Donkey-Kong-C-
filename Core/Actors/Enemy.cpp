#include "Enemy.h"
#include "../Physic/Collider.h"
#include <stdlib.h> 
#include <time.h>
#include "Hero.h"
#include "../Physic/StandardPhysicsComponent.h"

namespace DonkeyKong
{
	Enemy::Enemy(const Vec2 position) : GameObject(position, 49, 35, "Assets/donkey_kong_sheet.png"),
		barrelsPool{ 10, Vec2{120, 90} }, barrelAlreadyLaunched{ false },
		barrelsPileGameObj(std::make_unique<GameObject>(position + Vec2{ -25, 10 }, 36, 24, "Assets/barrels_pile.png")),
		launchBarrelRange{ 0, 2, 3, 4, 5 }, nextLaunch{ 0 }, hasLose{false}, timeToSwitchFalling {1.5}
	{
		Tag = "Enemy";

		colliderPtr = std::make_shared<Collider>(*this, sprite->SpriteRect());
		physicsComponent = std::make_unique<StandardPhysicsComponent>();
		physicsComponent->UseGravity = false;

		animations[AnimationName::idle] = std::make_shared<Animation>(3, 1.8f, Rect{ 0, 35, 49, 35 });
		animations[AnimationName::idle]->Name = static_cast<int>(AnimationName::idle);
		animations[AnimationName::launchBarrel] = std::make_shared<Animation>(3, 1.5f, Rect{ 0, 0, 49, 35 });
		animations[AnimationName::launchBarrel]->Name = static_cast<int>(AnimationName::launchBarrel);
		animations[AnimationName::launchBarrel]->Loop() = false;
		animations[AnimationName::surprised] = std::make_shared<Animation>(1, 100000, Rect{ 0, 70, 49, 35 });
		animations[AnimationName::headHitGround] = std::make_shared<Animation>(1, 400, Rect{ 0, 105, 49, 35 });

		currAnim = animations[AnimationName::idle];
		currAnim->Play(*sprite);

		srand(time(NULL));
		//nextLaunch = static_cast<float>(launchBarrelRange[rand() % launchBarrelRange.size()]);
	}

	void Enemy::Update(const Timer& timer)
	{
		GameObject::Update(timer);

		if (hasLose)
		{
			if (timeToSwitchFalling <= 0)
			{
				SetFallAnim();
			}
			else
				timeToSwitchFalling -= timer.DeltaTime();

			return;
		}

		barrelsLaunched.erase(std::remove_if(barrelsLaunched.begin(), barrelsLaunched.end(),
			[](auto&& b) {
			auto&& barrel = static_cast<Barrel&&>(*b);
			return barrel.Position().y > Renderer::WindowHeight || barrel.IsBreakAnimFinished();
		}),
			barrelsLaunched.end());

		for (auto&& barrel : barrelsLaunched)
		{
			barrel->Update(timer);
		}

		if (currAnim->Name == static_cast<int>(AnimationName::launchBarrel))
		{
			if (!currAnim->IsPlaying())
			{
				barrelAlreadyLaunched = false;
				currAnim = animations[AnimationName::idle];
				currAnim->Play(*sprite);
			}
			else if (currAnim->CurrFrame() == 2 && !barrelAlreadyLaunched)
			{
				barrelAlreadyLaunched = true;
				auto barrel = barrelsPool.GetObj();
				barrel->Roll(Vec2(120, 90), Vec2(100, 0));
				barrelsLaunched.push_back(std::move(barrel));
			}
		}
		else
		{
			if (nextLaunch <= 0)
			{
				currAnim = animations[AnimationName::launchBarrel];
				currAnim->Play(*sprite);
				nextLaunch = static_cast<float>(launchBarrelRange[rand() % launchBarrelRange.size()]);
			}
			else
				nextLaunch -= timer.DeltaTime();
		}
	}

	void Enemy::Draw(const Renderer& rend) const
	{
		GameObject::Draw(rend);

		if (!hasLose)
		{
			barrelsPileGameObj->Draw(rend);
			for (auto&& barrel : barrelsLaunched)
			{
				barrel->Draw(rend);
			}
		}
	}

	void Enemy::OnCollision(const Collider& other, const CollisionInfo info)
	{
		if (typeid(other.Owner()) == typeid(Hero))
		{
			static_cast<Hero&>(other.Owner()).Die();
		}
	}

	void Enemy::OnHeroWin()
	{
		if (!hasLose)
		{
			hasLose = true;
			SetSurprisedAnim();
		}
	}

	void Enemy::SetSurprisedAnim()
	{
		if (currAnim != animations[AnimationName::surprised])
		{
			currAnim = animations[AnimationName::surprised];
			currAnim->Play(*sprite);
		}
	}

	void Enemy::SetFallAnim()
	{
		if (velocity.y > 0)
			return;

		currAnim = animations[AnimationName::headHitGround];
		currAnim->Play(*sprite);
		physicsComponent->UseGravity = true;
	}
}
