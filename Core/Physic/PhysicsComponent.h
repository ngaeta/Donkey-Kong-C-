#pragma once

namespace DonkeyKong
{
	class Timer;
	class GameObject;

	class PhysicsComponent
	{
	public:
		virtual ~PhysicsComponent() = default;
		virtual void Update(GameObject&, const Timer&) = 0;

		bool UseGravity = false;
		bool UseAirResistence = false;
	};
}


