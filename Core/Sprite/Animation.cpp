#include "Animation.h"
#include <iostream>

namespace DonkeyKong
{
	//It's work only on a spritesheet with sequences of horizontal images
	Animation::Animation(const int frames, const int delayBetweenFrames, const Rect texture_rect_) :
		frames_count{ frames }, delay_frames{ delayBetweenFrames },
		loop{ true }, texture_rect{ texture_rect_ },
		curr_frame{ -1 }, next_frame_timer{ 0 }, is_playing{ false }, reverse{ false }
	{
	}

	void Animation::Tick(Sprite& sprite)
	{
		uint32_t currentTime = SDL_GetTicks();
		if (is_playing && static_cast<int>(currentTime) > next_frame_timer)
		{
			curr_frame += !reverse ? 1 : -1;

			if (curr_frame == frames_count || curr_frame == -1)
			{
				if (!loop)
				{
					is_playing = false;
					return;
				}
				else
				{
					curr_frame = !reverse ? 0 : frames_count - 1;
				}
			}

			sprite.TextureRect().x = curr_frame * sprite.TextureRect().w + texture_rect.x;
			next_frame_timer = currentTime + delay_frames;
		}
	}

	void Animation::Play(Sprite& sprite)
	{
		is_playing = true;
		curr_frame = reverse ? frames_count : -1;
		next_frame_timer = 0;
		sprite.TextureRect() = texture_rect;
		sprite.SetSize(texture_rect.w, texture_rect.h);
	}

	void Animation::Pause()
	{
		is_playing = false;
	}

	void Animation::SetReversed(const bool is_reversed)
	{
		this->reverse = is_reversed;
		curr_frame = reverse ? frames_count : -1;
	}

	bool& Animation::Loop()
	{
		return loop;
	}
}
