#ifndef LRECT_H
#define LRECT_H

#include "LGraphic.h"
#include "wSDL.h"


class LRect : public LGraphic
{
    public:
        LRect();
        virtual ~LRect();

        void SetSize(int w, int h);

        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue);
        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        virtual void SetBlendMode(SDL_BlendMode blending);

        virtual void SetAlpha(uint8_t alpha);

        virtual void Render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        uint8_t red, blue, green, alpha;

        SDL_BlendMode blend;
};

#endif // LRECT_H
