#include "Explosion.h"
#include "Weapon.h"

Explosion::Explosion(int frame_time, int x, int y)
    : LSprite(*wResources::texture_explosion.get(), 0, frame_time, LSprite::SPRITE_FORWARD | LSprite::SPRITE_DELETE)
{
    this->SetPosition(x - (m_width / 2), y - (m_height / 2));
    wResources::sound_explosion_mini->Play();
}

Explosion::~Explosion()
{}
