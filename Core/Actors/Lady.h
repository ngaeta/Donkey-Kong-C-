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

		const float TIME_TO_RETURN_IDLE;
		const std::array<float, 4> helpRange;
		float nextHelp;
		float returnToIdleTime;
		std::unordered_map<AnimationName, std::shared_ptr<Animation>> animations;
	};
}

