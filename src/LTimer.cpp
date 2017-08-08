#include "LTimer.h"

LTimer::LTimer()
{
    this->m_start_ticks = 0;
    this->m_paused_ticks = 0;

    this->m_started = false;
    this->m_paused = false;
}

void LTimer::Start()
{
    this->m_started = true;
    this->m_paused = false;

    this->m_start_ticks = SDL_GetTicks();
    this->m_paused_ticks = 0;
}

void LTimer::Stop()
{
    this->m_started = false;
    this->m_paused = false;
    this->m_start_ticks = 0;
    this->m_paused_ticks = 0;
}

void LTimer::Pause()
{
    if (this->m_started && !this->m_paused)
    {
        this->m_paused = true;
        this->m_paused_ticks = SDL_GetTicks() - this->m_start_ticks;
        this->m_start_ticks = 0;
    }
}

void LTimer::Unpause()
{
    if (this->m_started && this->m_paused)
    {
        this->m_paused = false;
        this->m_start_ticks = SDL_GetTicks() - this->m_paused_ticks;
        this->m_paused_ticks = 0;
    }
}

uint32_t LTimer::GetTicks()
{
    uint32_t time = 0;

    if (this->m_started)
    {
        if (this->m_paused)
            time = this->m_paused_ticks;
        else
            time = SDL_GetTicks() - this->m_start_ticks;
    }

    return time;
}

bool LTimer::IsStarted()
{
    return this->m_started;
}

bool LTimer::IsPaused()
{
    return this->m_paused && this->m_started;
}
