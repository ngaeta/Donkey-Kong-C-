#pragma once

#include <unordered_map>
#include <memory>
#include "../GameObject/GameObject.h"

namespace DonkeyKong
{
	class State;

	class StateMachine
	{
	public:
		StateMachine(GameObject&  _owner);
		virtual ~StateMachine() = default;

		void Input() const;
		void Update(const Timer& t) const;
		void OnCollision(const Collider& other, const CollisionInfo collisionInfo) const;
		void SwitchState(int id);

		inline GameObject& Owner() const { return owner; }

	protected:
		void RegisterState(int id, std::shared_ptr<State> state);	

	private:
		std::shared_ptr<State> currentState;
		std::unordered_map<int, std::shared_ptr<State>> states;
		GameObject& owner;
	};
}

