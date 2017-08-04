#include "Projectile.h"
#include <cmath>

Projectile::Projectile(DPoint start, Point target)
    : Entity("Projectile", "resources/bullet.png")
{
    this->m_box.x = start.x;
    this->m_box.y = start.y;

    this->m_target = target;

    this->m_angle = wSDL::GetAngle(start, target);

    this->m_vel.x = MAX_VEL * cos(m_angle * wSDL::PI / 180);
    this->m_vel.y = MAX_VEL * sin(m_angle * wSDL::PI / 180);

}

Projectile::Projectile(DRect start, Point target)
    : Projectile(DPoint {start.x + (start.w / 2) - (Projectile::WIDTH / 2), start.y + (start.h / 2) - (Projectile::HEIGHT / 2)}, target)
{}

Projectile::~Projectile()
{
    this->Free();
}

Tile* Projectile::Move(double time_step, std::vector<Tile*> tiles, Point level_size)
{
    return this->Entity::Move(time_step, tiles, level_size);
}

void Projectile::Free()
{
    this->Entity::Free();
}
