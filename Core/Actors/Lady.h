#pragma once

#include <unordered_map>
#include <array>
#include "../Game_Object/GameObject.h"

namespace DonkeyKong
{
	class Lady : public GameObject
	{
	public:
		Lady(const Vec2& pos);
		~Lady() = default;

		void Update(const Timer&)  override;
		void SetLoveAnimation();

	private:
		enum class AnimationName { idle, help, love };

		std::unordered_map<AnimationName, std::shared_ptr<Animation>> animations;
		float nextHelp;
		float currTimeToIdle;
		const std::array<float, 4> askingHelpRange;
		const float timeToReturnIdle;
	};
}

