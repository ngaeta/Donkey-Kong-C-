#pragma once

#include "StateMachine.h"
#include "../Physic/Collider.h"

namespace DonkeyKong
{ 
    class State
    {
    public:
        State() = default;
        virtual ~State() = default;

        void AssignStateMachine(StateMachine* _machine);

        virtual void Enter() = 0;
        virtual void Input() = 0;
        virtual void Update(const Timer& t) = 0;
        virtual void OnCollision(const Collider& other, const CollisionInfo collisionInfo) = 0;
        virtual void Exit() = 0;

    protected:
        StateMachine* machine;
    };
}

