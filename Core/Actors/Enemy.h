#pragma once

#include <unordered_map>
#include "../Game_Object/GameObject.h"
#include "../Pool/ObjectPool.h"
#include "../Game_Object/Barrel.h"
#include <array>
#include <functional>

namespace DonkeyKong
{
	class Enemy : public GameObject
	{
	public:
		Enemy() = delete;
		Enemy(const Vec2 position);
		~Enemy() = default;

		void Update(const Timer&)  override;
		void Draw(const Renderer&) const override;
		void OnCollision(const Collider& other, const CollisionInfo info) override;
		void OnHeroWin();

	private:
		enum class AnimationName { idle, launchBarrel, surprised, headHitGround };
		
		void SetSurprisedAnim();
		void SetFallAnim();

		const std::array<float, 5> launchBarrelRange;
		const std::unique_ptr<GameObject> barrels_pile;
		float nextLaunch;
		bool barrel_already_launched;
		bool hasLose;
		float timeToSwitchFalling;
		ObjectPool<Barrel> barrels_pool;
		std::vector<ObjectPool<Barrel>::ptr_type> barrels_active;
		std::unordered_map<AnimationName, std::shared_ptr<Animation>> animations;
		AnimationName currAnimationName;
	};
}

