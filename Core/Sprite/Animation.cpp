#include "Animation.h"
#include <iostream>

namespace DonkeyKong
{
	//It's work only on a spritesheet with sequences of horizontal images
	Animation::Animation(const int frames, const int delayBetweenFrames, const Rect texture_rect_) :
		framesCount{ frames }, delayBetweenFrames{ delayBetweenFrames },
		loop{ true }, texture_rect{ texture_rect_ },
		currFrame{ -1 }, nextFrameTimer{ 0 }, isPlaying{ false }, isReversed{ false }
	{
	}

	void Animation::Tick(Sprite& sprite)
	{
		uint32_t currentTime = SDL_GetTicks();
		if (isPlaying && static_cast<int>(currentTime) > nextFrameTimer)
		{
			currFrame += !isReversed ? 1 : -1;

			if (currFrame == framesCount || currFrame == -1)
			{
				if (!loop)
				{
					isPlaying = false;
					return;
				}
				else
				{
					currFrame = !isReversed ? 0 : framesCount - 1;
				}
			}

			sprite.TextureRect().x = currFrame * sprite.TextureRect().w + texture_rect.x;
			nextFrameTimer = currentTime + delayBetweenFrames;
		}
	}

	void Animation::Play(Sprite& sprite)
	{
		isPlaying = true;
		currFrame = isReversed ? framesCount : -1;
		nextFrameTimer = 0;
		sprite.TextureRect() = texture_rect;
		sprite.SetSize(texture_rect.w, texture_rect.h);
	}

	void Animation::Pause()
	{
		isPlaying = false;
	}

	void Animation::SetReversed(const bool is_reversed)
	{
		this->isReversed = is_reversed;
		currFrame = isReversed ? framesCount : -1;
	}

	bool& Animation::Loop()
	{
		return loop;
	}
}
