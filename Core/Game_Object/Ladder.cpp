#include "Ladder.h"
#include "../Physic/Collider.h"

namespace DonkeyKong
{
	Ladder::Ladder(Vec2 pos, unsigned int length_multiplier) : GameObject(pos, 15, 14, "Assets/ladder.png")
	{
		Tag = "Ladder";

		if (length_multiplier == 0) length_multiplier = 1;

		for (size_t i = 1; i < length_multiplier; i++)
		{
			pos.y += 14;
			sprites.push_back(std::make_unique<Sprite>(pos, 15, 14, "Assets/ladder.png"));
		}

		Rect rect = sprite->SpriteRect();
		//rect.h *= length_multiplier; problems with collision detection
		collider_ptr = std::make_shared<Collider>(*this, std::move(rect));

		if (length_multiplier > 1)
		{
			downCollider = std::make_shared<Collider>(*this, Rect{ rect.x, (int) pos.y - 14, rect.w, rect.h });
		}
	}

	void Ladder::Draw(const Renderer& renderer) const
	{
		GameObject::Draw(renderer);

		for (auto && sprite : sprites)
		{
			renderer.DrawSprite(*sprite);
		}

		if (DrawCollider && downCollider != nullptr)
		{
			downCollider->Draw(renderer);
		}
	}
}
