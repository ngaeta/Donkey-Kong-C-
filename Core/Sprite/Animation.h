#pragma once

#include <string>
#include <memory>
#include "Sprite.h"
#include "../Utility/Timer.h"

namespace DonkeyKong
{
	class Animation
	{
	public:
		Animation() = delete;
		Animation(const int frames, const float duration, const Rect texture_rect);
		~Animation() = default;

		void Tick(Sprite& sprite, const Timer& timer);
		void Play(Sprite& sprite);
		void Pause();

		void SetReversed(const bool is_reversed);
		bool& Loop();
		inline const bool& IsPlaying() const { return isPlaying; }
		inline const bool& IsReversed() const { return isReversed; }
		inline const int& CurrFrame() const { return currFrame; }

		int Name;

	private:
		int framesCount;
		int currFrame;
		float duration;
		float frameSpeed;
		float nextFrameTimer;
		bool loop;
		bool isPlaying;
		bool isReversed;
		Rect texture_rect;
	};
}

