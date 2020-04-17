#include "Lady.h"
#include "../Physic/Collider.h"

namespace DonkeyKong
{
	Lady::Lady(const Vec2& pos) : GameObject(pos, 16, 25, "Assets/peach.png"), 
		askingHelpRange{ 1, 4, 5, 7 }, nextHelp {1}, timeToReturnIdle {2.5}, currTimeToIdle { timeToReturnIdle }
	{
		collider_ptr = std::make_shared<Collider>(*this, Rect{ (int) pos.x, (int) pos.y, 16, 25 });
		collider_ptr->OffsetPos() = Vec2(8, 0);

		animations[AnimationName::idle] = std::make_shared<Animation>(1, 100, Rect{ 0, 0, 16, 25 });
		animations[AnimationName::idle]->Name = static_cast<int>(AnimationName::idle);
		animations[AnimationName::help] = std::make_shared<Animation>(2, 100, Rect{ 0, 30, 48, 25 });
		animations[AnimationName::help]->Name = static_cast<int>(AnimationName::help);
		animations[AnimationName::love] = std::make_shared<Animation>(2, 400, Rect{ 0, 63, 33, 25 });
		curr_animation = animations[AnimationName::idle];
		curr_animation->Play(*sprite);
	}

	void Lady::Update(const Timer& timer)
	{
		GameObject::Update(timer);

		if (curr_animation->Name == static_cast<int>(AnimationName::help))
		{
			if (currTimeToIdle <= 0)
			{
				curr_animation = animations[AnimationName::idle];
				curr_animation->Play(*sprite);
			}
			else
				currTimeToIdle -= timer.DeltaTime();
		}
		else 
		{
			if (nextHelp <= 0)
			{
				curr_animation = animations[AnimationName::help];
				curr_animation->Play(*sprite);
				currTimeToIdle = timeToReturnIdle;
				nextHelp = static_cast<float>(askingHelpRange[rand() % askingHelpRange.size()]);
			}
			else
				nextHelp -= timer.DeltaTime();
		}
	}

	void Lady::SetLoveAnimation()
	{
		if (curr_animation != animations[AnimationName::love])
		{
			curr_animation = animations[AnimationName::love];
			curr_animation->Play(*sprite);
		}
	}
}