#pragma once

#include <SDL.h>
#include <string>
#include <memory>
#include "../Utility/Vec2.h"
#include "Texture.h"
#include "../Utility/types.h"

namespace DonkeyKong
{
	class Sprite
	{
	public:
		Sprite() = delete;
		Sprite(const Vec2 pos, const int w, const int h, const std::string texture_fname);
		~Sprite() = default;

		void ScaleMultiplier(int multiplier);
		void SetSize(const int w, const int h);
		void FlipX(const bool value);

		inline const Texture& GetTexture() const { return *texture; }

		inline const Rect& TextureRect() const { return texture_rect; }
		Rect& TextureRect();

		const Rect& SpriteRect();
		Rect SpriteRect() const;

		Vec2& Position();
		float& Rotation();
		inline const float& Rotation() const { return rotation; }

		inline const FlipMode& GetFlipMode() const { return flipMode; }
		inline const Pivot& GetPivot() const { return pivot; }

	private:
		std::shared_ptr<Texture> texture;
		Vec2 position;
		float rotation;
		int scaleMultiplier;
		Rect spriteRect;
		Rect texture_rect;
		Pivot pivot;
		FlipMode flipMode;
	};
}
