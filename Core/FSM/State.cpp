#include "State.h"

namespace DonkeyKong
{
	void State::AssignStateMachine(StateMachine* _machine)
	{
		machine = _machine;
	}

	void State::Enter()
	{
	}
	void State::Input()
	{
	}
	void State::Update(const Timer& t)
	{
	}
}
