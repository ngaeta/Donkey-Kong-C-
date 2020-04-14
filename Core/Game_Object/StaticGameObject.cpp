#include "StaticGameObject.h"
#include "../Physic/Collider.h"

namespace DonkeyKong
{
	StaticGameObject::StaticGameObject(const Vec2 pos, const int w, const int h, const std::string texture_fname) 
		: GameObject(pos, w, h, texture_fname)
	{
		Tag = "StaticGameObj";

		collider_ptr = std::make_shared<Collider>(*this, sprite->SpriteRect());
	}

	void StaticGameObject::Update(const Timer &)
	{
	}

	void StaticGameObject::OnCollision(const Collider& other, const CollisionInfo info)
	{
	}
}
