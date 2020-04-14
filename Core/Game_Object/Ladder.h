#pragma once

#include <vector>
#include <memory>
#include "GameObject.h"
#include "../Utility/Vec2.h"

namespace DonkeyKong
{
	class Ladder : public GameObject
	{

	public:
		Ladder(Vec2 pos, const unsigned int ladder_length);
		~Ladder() = default;

		void Draw(const Renderer& renderer) const override;


	private:
		std::vector<std::shared_ptr<Sprite>> sprites;
		std::shared_ptr<Collider> downCollider;
	};
}

