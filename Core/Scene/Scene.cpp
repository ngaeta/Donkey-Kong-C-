#include "Scene.h"
#include "../GameObject/StaticGameObject.h"
#include "../GameObject/Ladder.h"
#include "../Actors/Enemy.h"
#include "../Actors/Hero.h"
#include "../Actors/Lady.h"
#include <math.h>
#include <time.h>

namespace DonkeyKong
{
	const Vec2 Scene::PLATFORM_START_POSITION = { 30, 100 };
	const Vec2 Scene::PLATFORM_END_POSITION = { 580, 500 };
	const Vec2 Scene::PLATFORM_OFFSET = { 36, 60 };
	const Vec2 Scene::ENEMY_OFFSET_FROM_PLATFORM = { 40, -32 };
	const Vec2 Scene::PLAYER_OFFSET_FROM_PLATFORM = { 10, -15 };
	const Vec2 Scene::LADY_OFFSET_FROM_HER_PLATFORM = { 2, -23 };
	const Vec2 Scene::LADY_PLATFORM_OFFSET_FROM_ENEMY = { 50, -20 };
	const Uint32 Scene::PLAYER_PLATFORM_LENGTH = 170;
	const Uint32 Scene::ENEMY_PLATFORM_LENGTH = 170;
	const Uint32 Scene::LADY_PLATFORM_LENGTH = 72;
	const int Scene::Y_PLATFORM_GRADIENT = 1;
	const int Scene::PLATFORM_SUBTRACT = 2;
	const float Scene::PLATFORM_ROTATION = 1;
	const float Scene::SINGLE_LADDER_SIZE = 14;

	Scene::Scene(const Renderer& renderer)
	{
		int yGradient = -Y_PLATFORM_GRADIENT;

		//Enemy and his platform positions
		Vec2 enemyPos = PLATFORM_START_POSITION + ENEMY_OFFSET_FROM_PLATFORM;

		Vec2 last_platform_placed = CreateHorizontal(PLATFORM_START_POSITION,  PLATFORM_START_POSITION.x + ENEMY_PLATFORM_LENGTH, false);
		//auto next_platform_pos = Vec2{ last_platform_placed.x + PLATFORM_OFFSET.x, PLATFORM_START_POSITION.y };
		auto next_platform_endX = PLATFORM_END_POSITION.x - (PLATFORM_OFFSET.x * PLATFORM_SUBTRACT);
		last_platform_placed = CreateHorizontal(last_platform_placed, next_platform_endX, true, Y_PLATFORM_GRADIENT, PLATFORM_ROTATION);

		//Peach Pos
		auto ladyPlatform = enemyPos + LADY_PLATFORM_OFFSET_FROM_ENEMY;
		CreateHorizontal(ladyPlatform, ladyPlatform.x + LADY_PLATFORM_LENGTH);

		//Platform position
		leftToRightConstruction = true;
		int y = last_platform_placed.y + PLATFORM_OFFSET.y;
		for (; y < PLATFORM_END_POSITION.y - PLATFORM_OFFSET.y * PLATFORM_SUBTRACT; y = last_platform_placed.y + PLATFORM_OFFSET.y)
		{
			Vec2 currPlatformPos = { (int) (PLATFORM_START_POSITION.x + (PLATFORM_OFFSET.x * leftToRightConstruction * PLATFORM_SUBTRACT)), y };
			last_platform_placed = CreateHorizontal(currPlatformPos, PLATFORM_END_POSITION.x - (PLATFORM_OFFSET.x * !leftToRightConstruction * PLATFORM_SUBTRACT), 
				true, yGradient, yGradient * PLATFORM_ROTATION);
			yGradient = -yGradient;
			leftToRightConstruction = !leftToRightConstruction;
		}

		//Player pos
		Vec2 playerPos = Vec2{ PLATFORM_START_POSITION.x + PLAYER_OFFSET_FROM_PLATFORM.x, y + PLAYER_OFFSET_FROM_PLATFORM.y };
		if (yGradient < 0)
		{
			last_platform_placed = CreateHorizontal(Vec2{ (int) PLATFORM_START_POSITION.x, y }, PLATFORM_START_POSITION.x + PLAYER_PLATFORM_LENGTH, false);
			CreateHorizontal(last_platform_placed, PLATFORM_END_POSITION.x, false, -Y_PLATFORM_GRADIENT, -PLATFORM_ROTATION);
		}
		else
		{
			last_platform_placed = CreateHorizontal(Vec2{ (int) PLATFORM_START_POSITION.x, y }, (PLATFORM_END_POSITION.x - PLATFORM_OFFSET.x * PLATFORM_SUBTRACT) - PLAYER_PLATFORM_LENGTH, false,
				Y_PLATFORM_GRADIENT, PLATFORM_ROTATION);
			CreateHorizontal(last_platform_placed, last_platform_placed.x + PLAYER_PLATFORM_LENGTH, false);
		}

		//Ladders
		CreateLadders(round(PLATFORM_OFFSET.y / SINGLE_LADDER_SIZE));

		//Props

		//Actors
		enemy = std::make_shared<Enemy>(enemyPos);
		goToDraw.push_back(enemy);

		hero = std::make_shared<Hero>(playerPos);
		goToDraw.push_back(hero);

		lady = std::make_shared<Lady>(Vec2{ ladyPlatform.x + LADY_OFFSET_FROM_HER_PLATFORM.x, ladyPlatform.y + LADY_OFFSET_FROM_HER_PLATFORM.y });
		goToDraw.push_back(lady);
	}

	void Scene::Draw(const Renderer& renderer) const
	{
		for (auto&& go : goToDraw)
		{
			go->Draw(renderer);
		}
	}

	void Scene::Update(const Timer& timer)
	{
		hero->Update(timer);
		if (hero->IsDead())
		{
			if(timeToStopUpdateAfterLose<= 0) 
				return;
			else 
				timeToStopUpdateAfterLose -= timer.DeltaTime();
		}
		
		enemy->Update(timer);
		lady->Update(timer);

		if (!hero->HasWon())
		{
			for (auto&& go : goToUpdate)
			{
				go->Update(timer);
			}
		}
		else 
		{
			enemy->OnHeroWin();
			goToDraw.erase(std::remove_if(goToDraw.begin(), goToDraw.end(),
				[](auto&& go) {
				return go->Position().y == PLATFORM_START_POSITION.y;
			}),
				goToDraw.end());
		}
	}

	const Vec2 Scene::CreateHorizontal(Vec2 startPos, const int xEnd, const bool createLadder, const int yOffset, const float rotation)
	{
		if (leftToRightConstruction && createLadder)
		{
			laddersPosition.push_back(Vec2{ startPos.x + PLATFORM_OFFSET.x, startPos.y });
		}

		for (; startPos.x < xEnd; startPos.x += PLATFORM_OFFSET.x, startPos.y += yOffset)
		{
			//TODO
			//optimize, gameobject does not use the same texture
			auto go = std::make_shared<StaticGameObject>(startPos, 36, 12, "assets/platform.png");
			go->Rotation() = rotation;
			goToDraw.push_back(std::move(go));
		}

		if (!leftToRightConstruction && createLadder)
		{
			laddersPosition.push_back(Vec2{ startPos.x - PLATFORM_OFFSET.x, startPos.y - yOffset });
		}

		return Vec2{ startPos.x, startPos.y };
	}

	void Scene::CreateLadders(const int ladder_size)
	{
		for (auto&& pos : laddersPosition)
		{
			goToDraw.push_back(std::make_shared<Ladder>(pos, ladder_size));
		}
	}
}
