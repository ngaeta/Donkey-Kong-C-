#include "Collider.h"
#include "CollisionHandler.h"
#include <stdlib.h> 
#include <iostream>

namespace DonkeyKong
{
	Collider::Collider(GameObject& go, const Rect& rect)
		: collider_rect{ rect }, owner_ptr{ go }, offsetPos {0}
	{
		CollisionHandler::AddCollider(this);
	}

	void Collider::Update()
	{
		collider_rect.x = Owner().Position().x + offsetPos.x;
		collider_rect.y = Owner().Position().y + offsetPos.y;
	}

	void Collider::Draw(const Renderer& renderer) const
	{
		renderer.DrawTransparentRect(collider_rect, 0, 255, 0, 100);
	}

	const bool Collider::CheckCollision(const Collider& other_collider, CollisionInfo& info) const
	{
		if (SDL_HasIntersection(&collider_rect, &other_collider.collider_rect))
		{
			float myHalfHeight = collider_rect.h * 0.5;
			float myHalfWidth = collider_rect.w * 0.5;
			float otherHalfWidth = other_collider.collider_rect.w * 0.5;
			float otherHalfHeight = other_collider.collider_rect.h * 0.5;
			Vec2 otherRectPos = Vec2(other_collider.collider_rect.x, other_collider.collider_rect.y);
			Vec2 myRectPos = Vec2(collider_rect.x, collider_rect.y);
			Vec2 distance = otherRectPos - myRectPos;
			float deltaX = abs(distance.x) -(myHalfWidth + otherHalfWidth);
			float deltaY = abs(distance.y) - (myHalfHeight + otherHalfHeight);

			info.Delta = Vec2(-deltaX, -deltaY);
			info.collider = &other_collider;

			return true;
		}

		return false;
	}
}
