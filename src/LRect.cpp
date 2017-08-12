#include "LRect.h"

LRect::LRect(int x, int y, int w, int h)
    : LRect(w, h)
{
    this->SetPosition(x, y, false);

}

LRect::LRect(int w, int h)
    : LTexture()
{
    this->SetSize(w, h);
    this->m_red = 0x00;
    this->m_blue = 0x00;
    this->m_green = 0x00;
    this->m_alpha = 0xFF;
    this->m_blend = SDL_BLENDMODE_BLEND;
}

LRect::~LRect()
{

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

void LRect::Render(SDL_Rect &camera, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect rect = SDL_Rect{m_box.x - camera.x, m_box.y - camera.y, m_box.w, m_box.h};
    SDL_SetRenderDrawColor(wSDL::s_renderer.get(), this->m_red, this->m_green, this->m_blue, this->m_alpha);
    SDL_SetRenderDrawBlendMode(wSDL::s_renderer.get(), this->m_blend);
    SDL_RenderFillRect(wSDL::s_renderer.get(), &rect);
}


void LRect::Render(SDL_Rect &camera, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SetPosition(x, y, false);
    this->Render(camera);
}

void LRect::Render()
{
    SDL_Rect zeros;
    this->Render(zeros);
}

void LRect::Render(int x, int y)
{
    SetPosition(x, y, false);
    SDL_Rect zeros;
    this->Render(zeros);
}
