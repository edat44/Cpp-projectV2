#include "Projectile.h"
#include <cmath>
#include "Weapon.h"
#include "Map.h"

Projectile::Projectile(Weapon* weapon, double speed, Point<double> start, Point<int> target)
    : Entity("Projectile", wResources::texture_bullet)
{
    SetPosition(start, true);

    this->m_weapon = weapon;

    this->m_speed = speed;

    this->m_target = target;

    this->m_angle = wSDL::GetAngle(start, target);

    this->m_vel.x = m_speed * cos(m_angle * wSDL::PI / 180);
    this->m_vel.y = m_speed * sin(m_angle * wSDL::PI / 180);

    this->m_spawn_time = SDL_GetTicks();

    this->LoadSounds();
    this->m_sound_spawn->Play();
}

Projectile::Projectile(Weapon *weapon, double speed, Rect<double> start, Point<int> target)
     : Projectile(weapon, speed, start.GetMiddle(), target)
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
    return (this->m_box == p.m_box) && (this->m_target == p.m_target) && (this->m_spawn_time == p.m_spawn_time);
}

Tile* Projectile::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point<int> level_size)
{
    double dx = (m_vel.x * time_step);
    double dy = (m_vel.y * time_step);
    m_box.x += dx;
    m_box.y += dy;
    Tile *wall = this->TouchesWall(tiles);

    bool done = false;

    Point<int> map_size = m_weapon->GetMap()->GetMapSizePixels();
    if (m_box.x < 0 || m_box.y < 0 || (m_box.x > map_size.x - m_box.w) || (m_box.y > map_size.y - m_box.h))
        done = true;

    if (wall != nullptr)
    {
        done = true;
        m_box.x -= (m_box.w / 2);
        m_box.y -= (m_box.h / 2);
    }

    if (done)
        m_weapon->DeleteProjectile(this);

    return wall;
}
