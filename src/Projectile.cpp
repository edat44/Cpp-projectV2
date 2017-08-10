#include "Projectile.h"
#include <cmath>
#include "Weapon.h"

Projectile::Projectile(DPoint start, Point target)
    : Entity("Projectile", wResources::texture_bullet)
{
    this->m_box.x = start.x;
    this->m_box.y = start.y;

    this->m_target = target;

    this->m_angle = wSDL::GetAngle(start, target);

    this->m_vel.x = MAX_VEL * cos(m_angle * wSDL::PI / 180);
    this->m_vel.y = MAX_VEL * sin(m_angle * wSDL::PI / 180);

    this->LoadSounds();
    this->m_sound_spawn->Play();

    this->m_done = false;
}

Projectile::Projectile(DRect start, Point target)
    : Projectile(DPoint {start.x + (start.w / 2) - (Projectile::WIDTH / 2), start.y + (start.h / 2) - (Projectile::HEIGHT / 2)}, target)
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
    double dx = (m_vel.x * time_step);
    double dy = (m_vel.y * time_step);
    m_box.x += dx;
    m_box.y += dy;
    Tile *wall = this->TouchesWall(tiles);

    if (m_box.x < 0 || m_box.y < 0 || (m_box.x > wSDL::SCREEN_WIDTH - m_box.w) || (m_box.y > wSDL::SCREEN_HEIGHT - m_box.h))
        m_done = true;

    if (wall != nullptr)
    {
        m_done = true;
        m_box.x -= (m_box.w / 2);
        m_box.y -= (m_box.h / 2);
    }

    return wall;
}

bool Projectile::Done()
{
    return m_done;
}
