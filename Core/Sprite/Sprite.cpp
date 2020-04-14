#include "Sprite.h"
#include "../Renderer/Renderer.h"
#include <iostream>
#include <string>
#include <SDL_rect.h>

namespace DonkeyKong
{
	Sprite::Sprite(const Vec2 pos, const int w, const int h, const std::string texture_fname) :
        is_active{true}, scale_multiplier {1}, flip_mode{SDL_FLIP_NONE},
		position{ pos }, rotation{ 0 }, spriteRect{ (int)pos.x, (int)pos.y, w, h },
		texture{ std::make_shared<Texture>(texture_fname) }, pivot{ w/2, h/2 }
	{
		SDL_QueryTexture(texture->GetRawPointer(), NULL, NULL, &texture_rect.w, &texture_rect.h);
	}

	const Rect & Sprite::SpriteRect()
	{
		spriteRect.x = (int)(position.x);
		spriteRect.y = (int)(position.y);
		return spriteRect;
	}

	Rect Sprite::SpriteRect() const
	{
		return Rect{ (int) (position.x), int (position.y), spriteRect.w * scale_multiplier, spriteRect.h * scale_multiplier};
	}

	void Sprite::SetSize(const int w, const int h)
	{
		spriteRect.w = w;
		spriteRect.h = h;
	}

	Vec2 & Sprite::Position()
	{
		return position;
	}

	float& Sprite::Rotation()
	{
		return rotation;
	}

	Rect & Sprite::TextureRect()
	{
		return texture_rect;
	}

	void Sprite::FlipX(const bool value)
	{
		flip_mode = value ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	}

    void Sprite::ScaleMultiplier(int multiplier) 
    {
        scale_multiplier = multiplier;
        spriteRect.w *= multiplier;
        spriteRect.h *= multiplier;
    }
}