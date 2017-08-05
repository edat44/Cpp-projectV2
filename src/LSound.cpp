#include "LSound.h"

LSound::LSound(std::string path)
{
    m_path_sound = path;
    m_sound = Mix_LoadWAV(path.c_str());
    if (m_sound == nullptr)
    {
        printf("Sound %s could not be loaded! Mix Error: %s\n", path.c_str(), Mix_GetError());
    }
}

LSound::~LSound()
{
    if (m_sound != nullptr)
    {
        Mix_FreeChunk(m_sound);
        m_sound = nullptr;
    }
}

bool LSound::Play(int channel, int loops)
{
    return Mix_PlayChannel(channel, m_sound, loops) < 0;
}
