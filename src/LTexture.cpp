#include "LTexture.h"

LTexture::LTexture()
{
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
}

LTexture::~LTexture()
{
    this->Free();
}

bool LTexture::LoadFromFile(std::string path)
{

    SDL_Texture *new_texture = nullptr;
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == nullptr || loaded_surface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));

        new_texture = SDL_CreateTextureFromSurface(wSDL::s_renderer, loaded_surface);
        if (new_texture == nullptr)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            this->m_width = loaded_surface->w;
            this->m_height = loaded_surface->h;
        }

        SDL_FreeSurface(loaded_surface);
    }

    m_texture = new_texture;
    return m_texture != nullptr;
}

#ifdef _SDL_TTF_H
bool LTexture::LoadFromRenderedText(std::string texture_text, SDL_Color text_color)
{
    this->Free();

    SDL_Surface* text_surface = TTF_RenderText_Solid(g_font, textureText.c_str(), text_color);
    if (text_surface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        m_texture = SDL_CreateTextureFromSurface(wSDL::s_renderer, text_surface);
        if (m_texture == nullptr)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            m_width = text_surface->w;
            m_height = text_surface->h;
        }

        SDL_FreeSurface(text_surface);
    }
    return m_texture != nullptr;
}
#endif // _SDL_TTF_H

void LTexture::Free()
{
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
}

void LTexture::SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void LTexture::SetBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(m_texture, blending);
}

void LTexture::SetAlpha(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(m_texture, alpha);
}

void LTexture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect render_quad = {x, y, m_width, m_height};

    if (clip != nullptr)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopyEx(wSDL::s_renderer, this->m_texture, clip, &render_quad, angle, center, flip);
}

int LTexture::GetWidth()
{
    return this->m_width;
}

int LTexture::GetHeight()
{
    return this->m_height;
}
