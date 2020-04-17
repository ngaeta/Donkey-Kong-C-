#pragma once

#include <string>
#include <memory>
#include "Sprite.h"

namespace DonkeyKong
{
	class Animation
	{
	public:
		Animation() = delete;
		Animation(const int frames, const int delayBetweenFrames, const Rect texture_rect);
		~Animation() = default;

		void Tick(Sprite& sprite);
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
		int delayBetweenFrames;
		int currFrame;
		int nextFrameTimer;
		bool loop;
		bool isPlaying;
		bool isReversed;
		Rect texture_rect;
	};
}

