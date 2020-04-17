#pragma once

#include <vector>
#include <memory>
#include "../GameObject/GameObject.h"

namespace DonkeyKong
{
	class Hero;
	class Enemy;
	class Lady;

	class Scene
	{
	public:
		Scene(const Renderer& renderer);
		Scene(const Scene&) = delete;
		Scene(Scene&&) = delete;
		void operator= (const Scene&) = delete;
		void operator= (Scene&&) = delete;
		~Scene() = default;

		void Draw(const Renderer& renderer) const;
		void Update(const Timer& renderer);

	private:
		const Vec2 CreateHorizontal(Vec2 startPos, const int xEnd, const bool createLadder = true, const int yOffset = 0, const float rotation = 0);
		void CreateLadders(const int ladder_size);

		static const Vec2 PLATFORM_START_POSITION;
		static const Vec2 PLATFORM_END_POSITION;
		static const Vec2 PLATFORM_OFFSET;
		static const Vec2 ENEMY_OFFSET_FROM_PLATFORM;
		static const Vec2 PLAYER_OFFSET_FROM_PLATFORM;
		static const Vec2 LADY_OFFSET_FROM_HER_PLATFORM;
		static const Vec2 LADY_PLATFORM_OFFSET_FROM_ENEMY;
		static const Uint32 PLAYER_PLATFORM_LENGTH;
		static const Uint32 ENEMY_PLATFORM_LENGTH;
		static const Uint32 LADY_PLATFORM_LENGTH;

		static const int PLATFORM_SUBTRACT;
		static const float PLATFORM_ROTATION;
		static const float SINGLE_LADDER_SIZE;
		static const int Y_PLATFORM_GRADIENT;

		std::vector<Vec2> laddersPosition;
		std::vector<std::shared_ptr<GameObject>> goToUpdate;
		std::vector<std::shared_ptr<GameObject>> goToDraw;
		std::shared_ptr<Hero> hero;
		std::shared_ptr<Enemy> enemy;
		std::shared_ptr<Lady> lady;
		float timeToStopUpdateAfterLose = 1;
		bool leftToRightConstruction;
	};
}

