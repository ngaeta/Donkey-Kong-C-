#ifndef AIV_RENDERER
#define AIV_RENDERER

#include "../Sprite/Sprite.h"
#include <SDL.h>

namespace DonkeyKong
{
	// struct SDL_Renderer;
	// struct SDL_Window;
	// struct SDL_Rect;

	class Renderer final
	{
	public:
		Renderer();
		~Renderer();

		bool Color(Uint8, Uint8, Uint8, Uint8) const;
		bool DrawRect(const SDL_Rect&) const;
		void DrawTransparentRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
		void DrawSprite(const Sprite&) const;
		void Present() const;
		bool Clear() const;

		explicit operator bool();

		static SDL_Renderer* Instance;
		static const int WindowWidth;
		static const int WindowHeight;

	private:
		SDL_Window* window;
		bool init;
	};
}

#endif
