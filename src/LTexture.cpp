#include "LTexture.h"
#include "LSprite.h"

LTexture::LTexture(std::string path, int clip_rows, int clip_cols, SDL_Color background_mask) try
{
    this->m_path = path;
    this->m_background_mask = background_mask;
    this->m_clip_rows = clip_rows;
    this->m_clip_cols = clip_cols;
    this->Load();
}
catch(std::exception &e)
{
    printf(e.what());
    throw;
}

LTexture::LTexture(const LTexture &texture)
{
    this->m_path = texture.m_path;
    this->m_background_mask = texture.m_background_mask;
    this->m_texture = texture.m_texture;
    this->m_clip_rows = texture.m_clip_rows;
    this->m_clip_cols = texture.m_clip_cols;
    this->m_box = texture.m_box;
}

LTexture::~LTexture()
{
}

void LTexture::Load()
{
    SDL_Surface *loaded_surface;
    loaded_surface = IMG_Load(m_path.c_str());
    if (loaded_surface == nullptr || loaded_surface == NULL)
    {
        throw std::runtime_error("Could not load surface for " + m_path + "! " + SDL_GetError() + "\n");
    }
    else
    {
        SDL_Color c = m_background_mask;
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, c.r, c.g, c.b));

        m_texture = sdl_shared(SDL_CreateTextureFromSurface(wSDL::s_renderer.get(), loaded_surface));
        if (!m_texture)
        {
            throw std::runtime_error("Could not load texture for " + m_path + "! " + SDL_GetError() + "\n");
        }
        else
        {
            SetSize(loaded_surface->w / m_clip_cols, loaded_surface->h / m_clip_rows);
        }
        SDL_FreeSurface(loaded_surface);
    }

}


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

void LTexture::Render(SDL_Rect &camera, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SetPosition(x, y, false);
    this->Render(camera, clip, angle, center, flip);
}

void LTexture::Render(SDL_Rect &camera, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect render_quad = {m_box.x - camera.x, m_box.y - camera.y, m_box.w, m_box.h};

    if (clip != nullptr)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    Rect<int> collision_rect = {m_box.x, m_box.y, render_quad.w, render_quad.h};
    if (wSDL::CheckCollision(collision_rect, camera))
        SDL_RenderCopyEx(wSDL::s_renderer.get(), this->m_texture.get(), clip, &render_quad, angle, center, flip);
}


PSprite LTexture::MakeSprite(int start_frame, int frame_time, SPRITE_MODE mode)
{
    return std::make_shared<LSprite>(*this, start_frame, frame_time, mode);
}
