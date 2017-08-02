#ifndef LGRAPHIC_H
#define LGRAPHIC_H

#include "wSDL.h"


class LGraphic
{
    public:
        LGraphic();
        virtual ~LGraphic();

        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue) = 0;

        virtual void SetBlendMode(SDL_BlendMode blending) = 0;

        virtual void SetAlpha(uint8_t alpha) = 0;

        virtual void Free();

        virtual void Render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE) = 0;

        int GetWidth();
        int GetHeight();

    protected:
        int m_width;
        int m_height;

    private:
};

#endif // LGRAPHIC_H
