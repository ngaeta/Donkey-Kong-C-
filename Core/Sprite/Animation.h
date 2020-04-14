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
		inline const bool& IsPlaying() const { return is_playing; }
		inline const bool& IsReversed() const { return reverse; }
		inline const int& CurrFrame() const { return curr_frame; }

		int Name;

	private:
		int frames_count;
		int delay_frames;
		int curr_frame;
		int next_frame_timer;
		bool loop;
		bool is_playing;
		bool reverse;
		Rect texture_rect;
	};
}

