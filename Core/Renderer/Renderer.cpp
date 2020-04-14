#include <SDL_render.h>
#include "Renderer.h"
#include <string.h>

namespace DonkeyKong 
{
    SDL_Renderer* Renderer::Instance;
    constexpr int Renderer::WindowWidth = 640;
    constexpr int Renderer::WindowHeight = 480;

    Renderer::Renderer(): init{}, window {nullptr}
    {
        if (!Instance)        
        {
            init = (SDL_CreateWindowAndRenderer(WindowWidth, WindowHeight, SDL_WINDOW_SHOWN, &window, &Instance) == 0);
            SDL_SetWindowTitle(window, " Donkey Kong by Nicola Gaeta");
        }
    }

    Renderer::~Renderer() 
    {
        if(init) 
        {
            SDL_DestroyRenderer(Instance);
            SDL_DestroyWindow(window);
        }
    }

    bool Renderer::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha)  const
    {
        return (SDL_SetRenderDrawColor(Instance, r, g, b, alpha) == 0);
    }

    bool Renderer::DrawRect(const SDL_Rect &rect) const 
    {
        return (SDL_RenderDrawRect(Instance, &rect) == 0);
    }

    void Renderer::DrawTransparentRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
    {
        SDL_SetRenderDrawBlendMode(Instance, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(Instance, 0, 255, 0, 100);
        SDL_RenderFillRect(Instance, &rect);
    }

    void Renderer::DrawSprite(const Sprite & sprite) const
    {
        SDL_RenderCopyEx(Instance, sprite.GetTexture().GetRawPointer(), &sprite.TextureRect(), &sprite.SpriteRect(), sprite.Rotation(), &sprite.GetPivot(), sprite.GetFlipMode());
    }

    void Renderer::Present() const 
    {
        SDL_RenderPresent(Instance);
    }

    bool Renderer::Clear() const 
    {
        return (SDL_RenderClear(Instance) == 0);
    }

    Renderer::operator bool() 
    {
        return init;
    }
}
