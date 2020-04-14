#pragma once

#include <queue>
#include <memory>
#include <cstdint>
#include <functional>

namespace DonkeyKong
{
	template<typename Object>
	class ObjectPool
	{	
	public:
		using ptr_type = std::unique_ptr<Object, std::function<void(Object*)>>;

		ObjectPool() = delete;
		~ObjectPool() = default;

		template<typename... Args>
		ObjectPool(const size_t pool_size, Args&&... args) : initial_size{pool_size}
		{
			for (size_t i = 0; i < pool_size; i++)
			{
				poolQueue.emplace(std::make_unique<Object>(std::forward<Args>(args)...));
			}
		}

		ptr_type GetObj() 
		{
			if (poolQueue.empty())
			{
				for (size_t i = 0; i < initial_size; i++)
				{
					poolQueue.emplace(std::make_unique<Object>());
				}
			}

			ptr_type tmp(poolQueue.front().release(),
				[this](Object* ptr) {
					this->AddObj(std::unique_ptr<Object>(ptr));
			});

			poolQueue.pop();
			return std::move(tmp);
		}

		void AddObj(std::unique_ptr<Object> object)
		{
			std::cout << "Enqueue obj " << std::endl;
			poolQueue.push(std::move(object));
		}
		
	private:
		const size_t initial_size;
		std::queue<std::unique_ptr<Object>> poolQueue;
	};
}

