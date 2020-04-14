#pragma once

#include "PhysicsComponent.h"

namespace DonkeyKong
{
	class StandardPhysicsComponent : public PhysicsComponent
	{
	public:
		const static float GRAVITY;
		const static float FRICTION_X;

		void Update(GameObject&, const Timer&) override;
	};
}

