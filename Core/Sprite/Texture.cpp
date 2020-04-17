#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "stb_image.h"
#include "SDL_render.h"
#include "SDL_log.h"
#include "../Renderer/Renderer.h"

namespace DonkeyKong
{
	Texture::Texture(const std::string file_name) : textureRawPtr{nullptr}
	{
		textureRawPtr = loadTexture(file_name.c_str());
	}

	Texture::~Texture()
	{
		SDL_DestroyTexture(textureRawPtr);
	}

	SDL_Texture * Texture::loadTexture(const std::string file_name) const
	{
		int width, height, channel;
		unsigned char* image = stbi_load(file_name.c_str(), &width, &height, &channel, 4);

		SDL_Texture* texture = SDL_CreateTexture(DonkeyKong::Renderer::Instance, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		Uint8 *pixels = nullptr;
		int pitch = 0;
		if (SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch))
		{
			SDL_Log("Texture not locked");
			return nullptr;
		}

		memcpy(pixels, image, pitch * height);
		free(image);
		SDL_UnlockTexture(texture);
		return texture;
	}
}
