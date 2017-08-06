#include "LSprite.h"

LSprite::LSprite(const LTexture &texture, int start_frame, int frame_time, SPRITE_MODE mode)
    : LTexture(texture)
{
    m_current_frame = start_frame;
    m_frame_time = frame_time;
    m_mode = mode;
    SetClips();
}

LSprite::~LSprite()
{}

void LSprite::SetClips()
{
    for (int y = 0; y < m_clip_rows; ++y)
    {
        for (int x = 0; x < m_clip_cols; ++x)
        {
            this->m_clips.push_back({x * m_width, y * m_height, m_width, m_height});
        }
    }
}

void LSprite::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    LTexture::Render(x, y, &m_clips.at(m_current_frame), angle, center, flip);
}
