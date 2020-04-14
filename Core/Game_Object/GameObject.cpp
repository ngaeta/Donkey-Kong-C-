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
          curr_animation{nullptr}, input_component{nullptr}, physics_component{nullptr},
		  velocity{ 0 }, rotation_speed{ 0 },collider_ptr{ nullptr }, Tag{ "No_tag" }, DrawCollider{ false }
	{
	}

	void GameObject::Update(const Timer &timer)
	{
		if (physics_component != nullptr)
		{
			physics_component->Update(*this, timer);
		}

		if (collider_ptr != nullptr)
		{
			collider_ptr->Update();
		}

		if (curr_animation != nullptr)
		{
			curr_animation->Tick(*sprite);
		}
	}

	void GameObject::Draw(const Renderer &renderer) const
	{
		if(sprite != nullptr)
			renderer.DrawSprite(*sprite);

		if (DrawCollider && collider_ptr != nullptr)
		{
			collider_ptr->Draw(renderer);
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

