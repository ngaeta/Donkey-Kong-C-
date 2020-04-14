#include "Enemy.h"
#include "../Game_Object/Barrel.h"
#include "../Physic/Collider.h"
#include <stdlib.h> 
#include <time.h>
#include "Hero.h"
#include "../Physic/StandardPhysicsComponent.h"

namespace DonkeyKong
{
	Enemy::Enemy(const Vec2 position) : GameObject(position, 49, 35, "Assets/donkey_kong_sheet.png"),
		barrels_pool{ 10, Vec2{120, 90} }, barrel_already_launched{ false },
		barrels_pile(std::make_unique<GameObject>(position + Vec2{ -25, 10 }, 36, 24, "Assets/barrels_pile.png")),
		launchBarrelRange{ 0, 2, 3, 4, 5 }, nextLaunch{ 0 }, hasLose{false}, timeToSwitchFalling {1.5}
	{
		Tag = "Enemy";

		collider_ptr = std::make_shared<Collider>(*this, sprite->SpriteRect());
		physics_component = std::make_unique<StandardPhysicsComponent>();
		physics_component->UseGravity = false;

		animations[AnimationName::idle] = std::make_shared<Animation>(3, 500, Rect{ 0, 35, 49, 35 });
		animations[AnimationName::idle]->Name = static_cast<int>(AnimationName::idle);
		animations[AnimationName::launchBarrel] = std::make_shared<Animation>(3, 400, Rect{ 0, 0, 49, 35 });
		animations[AnimationName::launchBarrel]->Name = static_cast<int>(AnimationName::launchBarrel);
		animations[AnimationName::launchBarrel]->Loop() = false;
		animations[AnimationName::surprised] = std::make_shared<Animation>(1, 400, Rect{ 0, 70, 49, 35 });
		animations[AnimationName::headHitGround] = std::make_shared<Animation>(1, 400, Rect{ 0, 105, 49, 35 });

		curr_animation = animations[AnimationName::idle];
		curr_animation->Play(*sprite);

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

		barrels_active.erase(std::remove_if(barrels_active.begin(), barrels_active.end(),
			[](auto&& b) {
			auto&& barrel = static_cast<Barrel&&>(*b);
			return barrel.Position().y > Renderer::WindowHeight || barrel.IsBreakAnimFinished();
		}),
			barrels_active.end());

		for (auto&& barrel : barrels_active)
		{
			barrel->Update(timer);
		}

		if (curr_animation->Name == static_cast<int>(AnimationName::launchBarrel))
		{
			if (!curr_animation->IsPlaying())
			{
				barrel_already_launched = false;
				curr_animation = animations[AnimationName::idle];
				curr_animation->Play(*sprite);
			}
			else if (curr_animation->CurrFrame() == 2 && !barrel_already_launched)
			{
				barrel_already_launched = true;
				auto barrel = barrels_pool.GetObj();
				barrel->Roll(Vec2(120, 90), Vec2(100, 0));
				barrels_active.push_back(std::move(barrel));
			}
		}
		else
		{
			if (nextLaunch <= 0)
			{
				curr_animation = animations[AnimationName::launchBarrel];
				curr_animation->Play(*sprite);
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
			barrels_pile->Draw(rend);
			for (auto&& barrel : barrels_active)
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
		if (curr_animation != animations[AnimationName::surprised])
		{
			curr_animation = animations[AnimationName::surprised];
			curr_animation->Play(*sprite);
		}
	}

	void Enemy::SetFallAnim()
	{
		if (velocity.y > 0)
			return;

		curr_animation = animations[AnimationName::headHitGround];
		curr_animation->Play(*sprite);
		physics_component->UseGravity = true;
	}
}
