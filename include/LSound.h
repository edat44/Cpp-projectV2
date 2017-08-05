#ifndef LSOUND_H
#define LSOUND_H

#include "wSDL.h"
#include <string>

class LSound
{
    public:
        LSound(std::string path);
        virtual ~LSound();

        bool Play(int channel = -1, int loops = 0);

    private:
        std::string m_path_sound;
        Mix_Chunk *m_sound;
};

#endif // LSOUND_H
