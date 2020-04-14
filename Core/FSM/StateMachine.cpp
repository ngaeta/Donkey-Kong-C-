#include "StateMachine.h"
#include "State.h"

namespace DonkeyKong
{
	StateMachine::StateMachine(GameObject&  _owner) : owner(_owner)
	{
	}

	void StateMachine::RegisterState(int id, std::shared_ptr<State> state)
	{
		states[id] = state;
		state->AssignStateMachine(this);  //use in state shared pointer al posto di statemachine* e scrivere enable shared from this
	}

	void StateMachine::SwitchState(int id)
	{
		if (currentState != nullptr)
		{
			currentState->Exit();
		}

		currentState = states[id];
		currentState->Enter();
	}

	void StateMachine::Input() const
	{
		if (currentState != nullptr)
		{
			currentState->Input();
		}
	}

	void StateMachine::Update(const Timer& t) const
	{
		if (currentState != nullptr)
		{
			currentState->Update(t);
		}
	}
	void StateMachine::OnCollision(const Collider& other, const CollisionInfo collisionInfo) const
	{
		currentState->OnCollision(other, collisionInfo);
	}
}
