#pragma once

#include "GameObject.h"

namespace DonkeyKong
{
	class StaticGameObject : public GameObject
	{
	public:
		StaticGameObject() = delete;
		StaticGameObject(const Vec2 pos, const int w, const int h, const std::string texture_fname);
		~StaticGameObject() = default;

		void Update(const Timer&) override;
		void OnCollision(const Collider& other, const CollisionInfo info) override;
	};
}

