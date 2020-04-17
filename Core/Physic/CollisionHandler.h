#pragma once

#include <vector>
#include <unordered_map>
#include "../GameObject/GameObject.h"
#include "Collider.h"

namespace DonkeyKong
{
	class CollisionHandler
	{
	public:
		CollisionHandler() = delete;
		CollisionHandler(const CollisionHandler&) = delete;
		CollisionHandler(CollisionHandler&&) = delete;
		void operator=(const CollisionHandler&) = delete;
		void operator = (CollisionHandler&&) = delete;
		~CollisionHandler() = default;

		static void CheckCollision();
		static void AddCollider(Collider*);

	private:
		static std::vector<Collider*> colliders;
	};
}

