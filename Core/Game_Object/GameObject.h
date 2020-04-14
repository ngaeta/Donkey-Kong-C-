#pragma once

#include <memory>
#include <string>
#include <iostream>
#include "../Sprite/Sprite.h"
#include "../Utility/Vec2.h"
#include "../Utility/Timer.h"
#include "../Input/InputComponent.h"
#include "../Sprite/Animation.h"
#include "../Renderer/Renderer.h"
#include "../Utility/types.h"
#include "../Physic/PhysicsComponent.h"
#include <vector>

//class Timer;
// class Renderer;
// class Animation;
//class InputComponent;

namespace DonkeyKong
{
	class Collider;
	struct CollisionInfo;

	class GameObject
	{
	public:
		GameObject() = delete;
		GameObject(const Vec2 pos, const int w, const int h, const std::string texture_fname);
		virtual ~GameObject() = default;

		virtual void Update(const Timer&);
		virtual void Draw(const Renderer&) const;
		virtual void OnCollision(const Collider& other, const CollisionInfo info);
		
		Vec2& Position();
		Vec2& Velocity();
		Sprite& GetSprite();
		float& Rotation();

		inline const float& RotationSpeed() const { return rotation_speed; }
		inline const Vec2& Velocity() const { return velocity; }
		inline const Sprite& GetSprite() const { return *sprite; }

		//Mainly for debugging
		std::string Tag;
		bool DrawCollider = false;

	protected:
		const std::shared_ptr<Sprite> sprite;
		std::shared_ptr<Animation> curr_animation;
		std::unique_ptr<InputComponent> input_component;
		std::unique_ptr<PhysicsComponent> physics_component;
		std::shared_ptr<Collider> collider_ptr;
		Vec2 velocity;
		float rotation_speed;
	};
}
