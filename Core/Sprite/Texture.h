#pragma once

#include <string>
#include <SDL.h>

namespace DonkeyKong
{
	class Texture
	{
	public:
		Texture() = delete;
		Texture(const std::string file_name);
		~Texture();

		inline SDL_Texture* GetRawPointer() const { return textureRawPtr; }

	private:
		SDL_Texture* loadTexture(const std::string file_name) const;

		SDL_Texture* textureRawPtr;
	};
}

