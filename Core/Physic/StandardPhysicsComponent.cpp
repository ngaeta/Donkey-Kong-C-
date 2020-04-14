#include "StandardPhysicsComponent.h"
#include "../Game_Object/GameObject.h"
#include "../Utility/Timer.h"
#include <math.h>


namespace DonkeyKong
{
	const float StandardPhysicsComponent::GRAVITY = 200.0f;
	const float StandardPhysicsComponent::FRICTION_X = 70.0f;

	void StandardPhysicsComponent::Update(GameObject & go, const Timer & timer)
	{
		Vec2 & vel = go.Velocity();

		if (UseGravity)
		{
			vel.y += GRAVITY * timer.DeltaTime();
		}

		if (UseAirResistence)
		{
			if (go.Velocity().x > 0)
			{
				vel.x -= FRICTION_X * timer.DeltaTime();
				if (vel.x < 0) vel.x = 0;
			} 
			else
			{
				vel.x += FRICTION_X * timer.DeltaTime();
				if (vel.x > 0) vel.x = 0;
			}
		}

		go.Position() += vel * timer.DeltaTime();
		go.Rotation() += go.RotationSpeed() * timer.DeltaTime();
	}
}
