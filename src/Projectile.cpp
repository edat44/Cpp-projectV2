#include "Projectile.h"
#include <cmath>

Projectile::Projectile(DPoint start, Point target,  std::function<void(Projectile* p)> clean_up_lambda)
    : Entity("Projectile", "resources/bullet.png")
{
    this->m_box.x = start.x;
    this->m_box.y = start.y;

    this->m_target = target;

    this->m_angle = wSDL::GetAngle(start, target);

    this->m_vel.x = MAX_VEL * cos(m_angle * wSDL::PI / 180);
    this->m_vel.y = MAX_VEL * sin(m_angle * wSDL::PI / 180);

    this->LoadSounds();
    this->m_sound_spawn->Play();

    this->CleanUp = clean_up_lambda;
}

Projectile::Projectile(DRect start, Point target,  std::function<void(Projectile* p)> clean_up_lambda)
    : Projectile(DPoint {start.x + (start.w / 2) - (Projectile::WIDTH / 2), start.y + (start.h / 2) - (Projectile::HEIGHT / 2)}, target, clean_up_lambda)
{}

Projectile::~Projectile()
{
    m_sound_wall->Play();
}

void Projectile::LoadSounds()
{
    m_sound_spawn = wResources::sound_bullet_fire;
    m_sound_wall = wResources::sound_bullet_wall;
}

bool Projectile::operator==(const Projectile &p)
{
    return this->m_box.x == p.m_box.x && this->m_box.y == p.m_box.y && this->m_angle == p.m_angle;
}

Tile* Projectile::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size)
{
    double dx = (m_vel.x * time_step);
    double dy = (m_vel.y * time_step);
    m_box.x = wSDL::Constrain(m_box.x + dx, 0, level_size.x - m_box.w);
    m_box.y = wSDL::Constrain(m_box.y + dy, 0, level_size.y - m_box.h);
    Tile* wall = this->TouchesWall(tiles);
    if (wall != nullptr)
    {
        this->CleanUp(this);
    }
    return wall;
}
