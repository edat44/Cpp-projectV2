#include "Projectile.h"
#include <cmath>
#define PI 3.14159265

const std::string Projectile::S_TEXTURE_PATH = "resources/bullet.png";
LTexture* Projectile::s_texture = nullptr;

Projectile::Projectile(DPoint start, Point target)
{
    this->m_box.x = start.x;
    this->m_box.y = start.y;
    this->m_box.w = Projectile::S_WIDTH;
    this->m_box.h = Projectile::S_HEIGHT;
    
    this->m_target = target;
    
    this->m_angle = wSDL::GetAngle(start, target);
    
    printf("angle: %f\n", m_angle);
    
    this->m_vel.x = S_MAX_VEL * cos(m_angle * PI / 180);
    this->m_vel.y = S_MAX_VEL * sin(m_angle * PI / 180);
}

Projectile::~Projectile()
{
    
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
    Projectile::s_texture->Render((int)m_box.x - camera.x, (int)m_box.y - camera.y, nullptr, m_angle);
}

bool Projectile::S_SetTexture()
{
    bool success = true;
    Projectile::s_texture = new LTexture();
    if (!Projectile::s_texture->LoadFromFile(Projectile::S_TEXTURE_PATH))
    {
        printf("Could not load player texture!\n");
        success = false;
    }
    
    return success;
}

void Projectile::S_Free()
{
    Projectile::s_texture->Free();
    delete Projectile::s_texture;
}
