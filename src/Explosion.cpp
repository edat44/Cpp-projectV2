#include "Explosion.h"
#include "Weapon.h"

Explosion::Explosion(Weapon *weapon, int frame_time, int x, int y)
    : LSprite(*wResources::texture_explosion.get(), 0, frame_time, LSprite::SPRITE_FORWARD | LSprite::SPRITE_DELETE)
{
    this->SetPosition(x, y, true);
    this->m_weapon = weapon;
    wResources::sound_explosion_mini->Play();
}

Explosion::~Explosion()
{}

bool Explosion::Update()
{
    bool done = this->LSprite::Update();
    if (done)
        m_weapon->DeleteExplosion(this);
    return done;
}
