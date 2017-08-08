#include "LFont.h"

LFont::LFont(std::string font_path, int pt_size, SDL_Color color, std::string text) try
{
    this->m_font_path = font_path;
    this->m_pt_size = pt_size;
    this->m_font = sdl_shared(TTF_OpenFont(font_path.c_str(), pt_size));
    this->m_color = color;
    this->m_text = text;
    this->Load();
}
catch (std::exception &e)
{
    printf(e.what());
    throw;
}

LFont::~LFont() {}

void LFont::Load()
{
    SDL_Surface *text_surface;
    if (m_text.length() == 0)
        m_text = " ";
    text_surface = TTF_RenderText_Solid(m_font.get(), m_text.c_str(), m_color);
    if (text_surface == nullptr)
    {
                throw std::runtime_error("Could not load font " + m_font_path + "! " + TTF_GetError());
    }
    else
    {
        m_texture = sdl_shared(SDL_CreateTextureFromSurface(wSDL::s_renderer.get(), text_surface));
        if (m_texture == nullptr)
        {
            throw std::runtime_error("Could not create texture for font " + m_font_path + "! " + TTF_GetError());
        }
        else
        {
            m_width = text_surface->w;
            m_height = text_surface->h;
        }
        SDL_FreeSurface(text_surface);
    }

}

void LFont::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect render_quad = {x, y, m_width, m_height};

    if (clip != nullptr)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopyEx(wSDL::s_renderer.get(), this->m_texture.get(), clip, &render_quad, angle, center, flip);
}

void LFont::ChangeText(std::string text)
{
    this->m_text = text;
    this->Load();
}

int LFont::GetWidth()
{
    return this->m_width;
}

int LFont::GetHeight()
{
    return this->m_height;
}
