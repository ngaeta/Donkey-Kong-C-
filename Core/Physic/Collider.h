#pragma once

#include <memory>
#include "../Utility/types.h"
#include "../Game_Object/GameObject.h"
#include "../Renderer/Renderer.h"

namespace DonkeyKong
{
	struct CollisionInfo
	{
		const Collider* collider;
		Vec2 Delta;
	};

	class Collider
	{
	public:
		Collider() = delete;
		Collider(GameObject& go, const Rect& rect);
		~Collider() = default;

		void Update();
		void Draw(const Renderer&) const;
		const bool CheckCollision(const Collider& other_collider, CollisionInfo& info) const;
		inline GameObject& Owner() const { return owner_ptr; }
		inline const Rect& ColliderRect() const { return collider_rect; }
		inline Vec2& OffsetPos() { return offsetPos; }

	private:
		GameObject & owner_ptr;
		Rect collider_rect;
		Vec2 offsetPos;
	};
}

