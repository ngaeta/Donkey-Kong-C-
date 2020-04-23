#include "GameObject.h"
#include "../Renderer/Renderer.h"
#include "../Physic/PhysicsComponent.h"
#include "../Sprite/Animation.h"
#include <iostream>
#include "../Physic/Collider.h"

namespace DonkeyKong
{
	GameObject::GameObject(const Vec2 pos, int w, int h, std::string texture_fname) 
        : sprite{ std::make_unique<Sprite>(pos, w, h, texture_fname) },
          currAnim{nullptr}, inputComponent{nullptr}, physicsComponent{nullptr},
		  velocity{ 0 }, rotationSpeed{ 0 },colliderPtr{ nullptr }, Tag{ "No_tag" }, DrawCollider{ false }
	{
	}

	void GameObject::Update(const Timer &timer)
	{
		if (physicsComponent != nullptr)
		{
			physicsComponent->Update(*this, timer);
		}

		if (colliderPtr != nullptr)
		{
			colliderPtr->Update();
		}

		if (currAnim != nullptr)
		{
			currAnim->Tick(*sprite, timer);
		}
	}

	void GameObject::Draw(const Renderer &renderer) const
	{
		if(sprite != nullptr)
			renderer.DrawSprite(*sprite);

		if (DrawCollider && colliderPtr != nullptr)
		{
			colliderPtr->Draw(renderer);
		}
	}

	void GameObject::OnCollision(const Collider& other, const CollisionInfo info)
	{
	}

	Vec2 & GameObject::Position() 
    {
		return sprite->Position();
	}

    Vec2 & GameObject::Velocity() 
    {
        return velocity;
    }

	float& GameObject::Rotation()
	{
		return sprite->Rotation();
	}

	Sprite & GameObject::GetSprite()
	{
		return *sprite;
	}
}

