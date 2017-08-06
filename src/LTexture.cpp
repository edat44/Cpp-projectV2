#include "LTexture.h"

LTexture::LTexture()
{
    m_texture = nullptr;
}

LTexture::~LTexture()
{
}

bool LTexture::LoadFromFile(std::string path)
{
    std::shared_ptr<SDL_Surface> loaded_surface;
    loaded_surface = sdl_shared(IMG_Load(path.c_str()));
    if (loaded_surface == nullptr || loaded_surface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loaded_surface.get(), SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0xFF, 0xFF, 0xFF));

        m_texture = sdl_shared(SDL_CreateTextureFromSurface(wSDL::s_renderer.get(), loaded_surface.get()));
        if (m_texture == nullptr)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            this->m_width = loaded_surface->w;
            this->m_height = loaded_surface->h;
        }
    }
    return true;
}

#ifdef _SDL_TTF_H
bool LTexture::LoadFromRenderedText(std::string texture_text, std::shared_ptr<TTF_Font> font, SDL_Color text_color)
{

    std::shared_ptr<SDL_Surface> text_surface;
    text_surface.reset(TTF_RenderText_Solid(font.get(), texture_text.c_str(), text_color));
    if (text_surface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        m_texture = sdl_shared(SDL_CreateTextureFromSurface(wSDL::s_renderer.get(), text_surface.get()));
        if (m_texture == nullptr)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            m_width = text_surface->w;
            m_height = text_surface->h;
        }
    }
    return m_texture != nullptr;
}
#endif // _SDL_TTF_H

void LTexture::SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    SDL_SetTextureColorMod(m_texture.get(), red, green, blue);
}

void LTexture::SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    this->SetColor(red, green, blue);
    this->SetAlpha(alpha);
}

void LTexture::SetBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(m_texture.get(), blending);
}

void LTexture::SetAlpha(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(m_texture.get(), alpha);
}

void LTexture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect render_quad = {x, y, m_width, m_height};

    if (clip != nullptr)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    SDL_RenderCopyEx(wSDL::s_renderer.get(), this->m_texture.get(), clip, &render_quad, angle, center, flip);
}

int LTexture::GetWidth()
{
    return this->m_width;
}

int LTexture::GetHeight()
{
    return this->m_height;
}
