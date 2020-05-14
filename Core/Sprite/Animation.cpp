#include "Animation.h"
#include <iostream>

namespace DonkeyKong
{
	Animation::Animation(const int frames, const float duration, const Rect texture_rect_) :
		framesCount{ frames }, duration{ duration },
		loop{ true }, texture_rect{ texture_rect_ },
		currFrame{ -1 }, nextFrameTimer{ 0 }, isPlaying{ false }, isReversed{ false }
	{
		frameSpeed = duration / framesCount;
	}

	void Animation::Tick(Sprite& sprite, const Timer& timer) 
	{
		if (isPlaying)
		{
			if (nextFrameTimer <= 0)
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
				nextFrameTimer = frameSpeed;
			}
			else
				nextFrameTimer -= timer.DeltaTime();	
		}
	}

	void Animation::Play(Sprite& sprite)
	{
		sprite.TextureRect() = texture_rect;
		sprite.SetSize(texture_rect.w, texture_rect.h);

		if (framesCount > 1)
		{
			isPlaying = true;
			currFrame = isReversed ? framesCount : -1;
			nextFrameTimer = 0;		
		}
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
