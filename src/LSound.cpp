#include "LSound.h"

LSound::LSound(std::string path)
{
    m_path = path;
    this->Load();
}

LSound::~LSound()
{}


bool LSound::Load()
{
    m_sound = make_unique_mix_chunk(LoadWAV(m_path));
    return m_sound != nullptr;
}

bool LSound::Play(int channel, int loops)
{
    return Mix_PlayChannel(channel, m_sound.get(), loops) < 0;
}

Mix_Chunk* LSound::LoadWAV(std::string path)
{
    return Mix_LoadWAV(path.c_str());
}
