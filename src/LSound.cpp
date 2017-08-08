#include "LSound.h"

LSound::LSound(std::string path) try
{
    m_path = path;
    this->Load();
}
catch(std::exception &e)
{
    printf("%s", e.what());
    throw;
}

LSound::~LSound()
{}


void LSound::Load()
{
    m_sound = make_unique_mix_chunk(LoadWAV(m_path));
    if (!m_sound)
        throw std::runtime_error("Could not load sound " + m_path + "! " + Mix_GetError() + "\n");
}

bool LSound::Play(int channel, int loops)
{
    return Mix_PlayChannel(channel, m_sound.get(), loops) < 0;
}

Mix_Chunk* LSound::LoadWAV(std::string path)
{
    return Mix_LoadWAV(path.c_str());
}
