#ifndef LRECT_H
#define LRECT_H

#include "wSDL.h"
#include "Box.h"

class LRect : public Box<int>
{
    public:
        LRect(int x, int y, int w, int h);
        virtual ~LRect();

        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue);
        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        virtual void SetBlendMode(SDL_BlendMode blending);

        virtual void SetAlpha(uint8_t alpha);

        virtual void Render(int x, int y);
        virtual void Render();

    private:
        uint8_t m_red, m_blue, m_green, m_alpha;

        SDL_BlendMode m_blend;
};

#endif // LRECT_H
