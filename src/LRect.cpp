#include "LRect.h"

LRect::LRect() : LGraphic()
{
    this->red = 0x00;
    this->blue = 0x00;
    this->green = 0x00;
    this->alpha = 0x00;
    this->blend = SDL_BLENDMODE_NONE;
}

LRect::~LRect()
{
    this->Free();
}

void LRect::Free()
{
    this->LGraphic::Free();
}

void LRect::SetSize(int w, int h)
{
    this->m_width = w;
    this->m_height = h;
}

void LRect::SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    this->red = red;
    this->blue = blue;
    this->green = green;
}

void LRect::SetBlendMode(SDL_BlendMode blending)
{
    this->blend = blending;
}

void LRect::SetAlpha(uint8_t alpha)
{
    this->alpha = alpha;
}

void LRect::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect rect = {x, y, this->m_width, this->m_height};
    SDL_SetRenderDrawColor(wSDL::s_renderer, this->red, this->green, this->blue, this->alpha);
    SDL_SetRenderDrawBlendMode(wSDL::s_renderer, this->blend);
    SDL_RenderFillRect(wSDL::s_renderer, &rect);
}
