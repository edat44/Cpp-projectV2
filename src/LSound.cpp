#include "LSound.h"

LSound::LSound(std::string path)
{
    m_path_sound = path;
    m_sound = make_unique_mix_chunk(LoadWAV(path));
    if (m_sound == nullptr)
    {
        printf("Sound %s could not be loaded! Mix Error: %s\n", path.c_str(), Mix_GetError());
    }
}

LSound::~LSound()
{
}

bool LSound::Play(int channel, int loops)
{
    return Mix_PlayChannel(channel, m_sound.get(), loops) < 0;
}

Mix_Chunk* LSound::LoadWAV(std::string path)
{
    return Mix_LoadWAV(path.c_str());
}
