#include "LSprite.h"

LSprite::LSprite(LTexture *texture, int start_frame, int frame_time, SPRITE_MODE mode)
    : LTexture(texture)
{
    m_current_frame = start_frame;
    m_frame_time = frame_time;
    m_mode = mode;
    m_completions = 0;
    SetClips();

    if (frame_time > 0)
    {
        m_frame_timer = std::unique_ptr<LTimer>(new LTimer());
        m_frame_timer->Start();
    }

    if ((m_mode & SPRITE_FORWARD) || (m_mode & SPRITE_FORWARD_BACKWARD))
    {
        m_frame_direction = 1;
        if ((m_mode & SPRITE_FORWARD) && (m_mode & SPRITE_FORWARD_BACKWARD))
            m_mode &= ~SPRITE_FORWARD_BACKWARD;
    }
    else if ((m_mode & SPRITE_BACKWARD) || (m_mode & SPRITE_BACKWARD_FORWARD))
    {
        m_frame_direction = -1;
        if ((m_mode & SPRITE_BACKWARD) && (m_mode & SPRITE_BACKWARD_FORWARD))
            m_mode &= ~SPRITE_BACKWARD_FORWARD;
    }
    else
    {
        m_frame_direction = 0;
        m_mode |= SPRITE_STATIC;
    }

    //Only repeat or delete mode (default to repeat)
    if ((m_mode & SPRITE_REPEAT) && (m_mode & SPRITE_DELETE))
        m_mode &= ~SPRITE_DELETE;
    if (!(m_mode & SPRITE_REPEAT) && !(m_mode & SPRITE_DELETE))
        m_mode |= SPRITE_REPEAT;
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

void LSprite::Render(SDL_Rect &camera, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    LTexture::Render(camera, &m_clips.at(m_current_frame), angle, center, flip);
}


void LSprite::Render(SDL_Rect &camera, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    m_pos.x = x;
    m_pos.y = y;
    this->Render(camera, clip, angle, center, flip);
}

bool LSprite::Update()
{
   if (m_frame_time > 0 && m_frame_timer->GetTicks() >= m_frame_time)
    {
        m_current_frame += m_frame_direction;
        if (m_current_frame == m_clips.size() - 1 || m_current_frame == 0)
        {
            ++m_completions;
            if (m_mode & SPRITE_DELETE)
            {
                if  ((m_completions == 1) && ((m_mode & SPRITE_FORWARD) || (m_mode & SPRITE_BACKWARD)))
                {
                    m_frame_direction *= -1;
                }
                else
                {
                    return false;
                }
            }
            else //Repeat Mode
            {
                if (m_frame_direction == 1)
                {
                    if ((m_mode & SPRITE_FORWARD) || (m_mode & SPRITE_BACKWARD_FORWARD))
                        m_current_frame = 0;
                    else
                        m_current_frame = m_clips.size() - 1;
                }
                else
                {
                    if ((m_mode & SPRITE_BACKWARD) || (m_mode & SPRITE_BACKWARD_FORWARD))
                        m_current_frame = m_clips.size() - 1;
                    else
                        m_current_frame = 0;
                }
            }
        }
        m_frame_timer->Start();
    }
    return true;
}

