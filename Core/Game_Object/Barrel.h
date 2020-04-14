#pragma once

#include <unordered_map>
#include "GameObject.h"

namespace DonkeyKong
{
	class Barrel : public GameObject
	{
	public:
		Barrel();
		Barrel(const Vec2 position);
		~Barrel() = default;

		void Update(const Timer&)  override;
		void OnCollision(const Collider& other, const CollisionInfo info) override;
		void Roll(const Vec2& pos, const Vec2& speed);

		const bool& IsBreakAnimFinished() const;

	private:
		enum class AnimationName { idle, roll, breaked };

		void Break();

		Vec2 speed;
		std::unordered_map<AnimationName, std::shared_ptr<Animation>> animations;
		bool isGrounded;
		bool isBreaked;
		int rotationSpeedMultiplier;
	};
}

