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

		inline const float& RotationSpeed() const { return rotationSpeed; }
		inline const Vec2& Velocity() const { return velocity; }
		inline const Sprite& GetSprite() const { return *sprite; }

		//Mainly for debugging
		std::string Tag;
		bool DrawCollider = false;

	protected:
		std::unique_ptr<InputComponent> inputComponent;
		std::unique_ptr<PhysicsComponent> physicsComponent;
		std::shared_ptr<Collider> colliderPtr;
		std::shared_ptr<Animation> currAnim;
		Vec2 velocity;
		float rotationSpeed;
		const std::shared_ptr<Sprite> sprite;
	};
}
