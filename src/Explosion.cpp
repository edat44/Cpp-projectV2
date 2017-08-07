#include "Explosion.h"
#include "Weapon.h"

Explosion::Explosion(Weapon *weapon, int frame_time, int x, int y)
    : LSprite(*wResources::texture_explosion.get(), 0, frame_time, LSprite::SPRITE_FORWARD | LSprite::SPRITE_DELETE)
{
    this->m_weapon = weapon;
    this->SetPosition(x - (m_width / 2), y - (m_height / 2));
}

Explosion::~Explosion()
{
    //this->m_weapon->DeleteExplosion(this);
}

void Explosion::Render(SDL_Rect &camera)
{
    LSprite::Render(camera, m_pos.x, m_pos.y);
}
