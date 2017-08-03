#ifndef LTIMER_H
#define LTIMER_H

#include "wSDL.h"

class LTimer
{
    public:
        LTimer();

        void Start();
        void Stop();
        void Pause();
        void Unpause();

        uint32_t GetTicks();

        bool IsStarted();
        bool IsPaused();

    private:
        uint32_t m_start_ticks;
        uint32_t m_paused_ticks;

        bool m_started;
        bool m_paused;
};

#endif // LTIMER_H
