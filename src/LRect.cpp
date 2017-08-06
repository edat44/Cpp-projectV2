#include "LRect.h"

LRect::LRect()
{
    this->m_red = 0x00;
    this->m_blue = 0x00;
    this->m_green = 0x00;
    this->m_alpha = 0xFF;
    this->m_blend = SDL_BLENDMODE_BLEND;
}

LRect::~LRect()
{

}

void LRect::SetSize(int w, int h)
{
    this->m_width = w;
    this->m_height = h;
}

void LRect::SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    this->m_red = red;
    this->m_blue = blue;
    this->m_green = green;
}

void LRect::SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    this->SetColor(red, green, blue);
    this->SetAlpha(alpha);
}

void LRect::SetBlendMode(SDL_BlendMode blending)
{
    this->m_blend = blending;
}

void LRect::SetAlpha(uint8_t alpha)
{
    this->m_alpha = alpha;
}

void LRect::Render(int x, int y)
{
    SDL_Rect rect = {x, y, this->m_width, this->m_height};
    SDL_SetRenderDrawColor(wSDL::s_renderer.get(), this->m_red, this->m_green, this->m_blue, this->m_alpha);
    SDL_SetRenderDrawBlendMode(wSDL::s_renderer.get(), this->m_blend);
    SDL_RenderFillRect(wSDL::s_renderer.get(), &rect);
}

int LRect::GetWidth()
{
    return this->m_width;
}

int LRect::GetHeight()
{
    return this->m_height;
}
