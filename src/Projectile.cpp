#include "Projectile.h"
#include <cmath>
#include "Weapon.h"

Projectile::Projectile(Weapon* weapon, DPoint start, Point target)
    : Entity("Projectile", wResources::texture_bullet)
{
    this->m_weapon = weapon;
    this->DeleteMe = [this]() {m_weapon->DeleteProjectile(this);};
    this->m_box.x = start.x;
    this->m_box.y = start.y;

    this->m_target = target;

    this->m_angle = wSDL::GetAngle(start, target);

    this->m_vel.x = MAX_VEL * cos(m_angle * wSDL::PI / 180);
    this->m_vel.y = MAX_VEL * sin(m_angle * wSDL::PI / 180);

    this->LoadSounds();
    this->m_sound_spawn->Play();
}

Projectile::Projectile(Weapon* weapon, DRect start, Point target)
    : Projectile(weapon, DPoint {start.x + (start.w / 2) - (Projectile::WIDTH / 2), start.y + (start.h / 2) - (Projectile::HEIGHT / 2)}, target)
{}

Projectile::~Projectile()
{
}

void Projectile::LoadSounds()
{
    m_sound_spawn = wResources::sound_bullet_fire;
}

bool Projectile::operator==(const Projectile &p)
{
    return this->m_box.x == p.m_box.x && this->m_box.y == p.m_box.y && this->m_angle == p.m_angle;
}

Tile* Projectile::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size)
{
    Tile *wall = this->TouchesWall(tiles);
    if (wall != nullptr)
    {
        this->DeleteMe();
    }
    double dx = (m_vel.x * time_step);
    double dy = (m_vel.y * time_step);
    m_box.x = wSDL::Constrain(m_box.x + dx, 0, level_size.x - m_box.w);
    m_box.y = wSDL::Constrain(m_box.y + dy, 0, level_size.y - m_box.h);
    wall = this->TouchesWall(tiles);
    return wall;
}
