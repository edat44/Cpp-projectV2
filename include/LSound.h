#ifndef LSOUND_H
#define LSOUND_H

#include "wSDL.h"
#include <string>
#include <memory>

class LSound
{
    public:
        LSound(std::string path);
        virtual ~LSound();

        bool Play(int channel = -1, int loops = 0);

    private:
        std::string m_path;
        sdl_unique_mix_chunk m_sound;

        Mix_Chunk* LoadWAV(std::string path);
        void Load();
};

#endif // LSOUND_H
