#ifndef LRECT_H
#define LRECT_H

#include "wSDL.h"
#include "LTexture.h"

class LRect : public LTexture
{
    public:
        LRect(int x, int y, int w, int h);
        LRect(int w, int h);
        virtual ~LRect();

        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue);
        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        virtual void SetBlendMode(SDL_BlendMode blending);

        virtual void SetAlpha(uint8_t alpha);

        virtual void Render(SDL_Rect &camera, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
        virtual void Render(SDL_Rect &camera, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void Render();
        void Render(int x, int y);

    private:
        uint8_t m_red, m_blue, m_green, m_alpha;

        SDL_BlendMode m_blend;
};

#endif // LRECT_H
