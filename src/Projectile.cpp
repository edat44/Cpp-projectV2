#include "Projectile.h"
#include <cmath>

const std::string Projectile::m_path_texture = "resources/bullet.png";

Projectile::Projectile(DPoint start, Point target)
{
    this->m_box.x = start.x;
    this->m_box.y = start.y;
    this->m_box.w = Projectile::S_WIDTH;
    this->m_box.h = Projectile::S_HEIGHT;

    this->m_target = target;

    this->m_angle = wSDL::GetAngle(start, target);

    this->m_vel.x = S_MAX_VEL * cos(m_angle * wSDL::PI / 180);
    this->m_vel.y = S_MAX_VEL * sin(m_angle * wSDL::PI / 180);

    this->LoadTexture();
}

Projectile::~Projectile()
{
    this->Free();
}

void Projectile::Move(double time_step, std::vector<Tile*> tiles, Point level_size)
{
    double dx = (m_vel.x * time_step);
    double dy = (m_vel.y * time_step);
    m_box.x += dx;
    m_box.y += dy;
}

void Projectile::Render(SDL_Rect &camera)
{
    this->m_texture->Render((int)m_box.x - camera.x, (int)m_box.y - camera.y, nullptr, m_angle);
}

bool Projectile::LoadTexture()
{
    bool success = true;
    this->m_texture = new LTexture();
    if (!this->m_texture->LoadFromFile(this->m_path_texture))
    {
        printf("Could not load player texture!\n");
        success = false;
    }

    return success;
}

void Projectile::Free()
{
    if (this->m_texture != nullptr)
    {
        this->m_texture->Free();
        delete this->m_texture;
    }
}
