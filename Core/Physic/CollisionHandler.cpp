#include "CollisionHandler.h"
#include <iostream>

namespace DonkeyKong
{
	std::vector<Collider*> CollisionHandler::colliders;

	void CollisionHandler::CheckCollision()
	{
		CollisionInfo info;
		size_t num_colliders = colliders.size();

		for (size_t i = 0; i < num_colliders; i++)
		{
			Collider* first = colliders.at(i);

			for (size_t j = i + 1; j < num_colliders; j++)
			{
				Collider* second = colliders.at(j);

				if (first->CheckCollision(*second, info))
				{
					first->Owner().OnCollision(*second, info);
					second->Owner().OnCollision(*first, info);
				}
			}
		}
	}

	void CollisionHandler::AddCollider(Collider* collider)
	{
		colliders.push_back(collider);
	}
}
