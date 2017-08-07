#include "Weapon.h"
#include "Player.h"

Weapon::Weapon(Player *player)
{
    m_player = player;
}

Weapon::~Weapon()
{
    this->m_projectiles.erase(this->m_projectiles.begin(), this->m_projectiles.end());
}

void Weapon::Fire(Point target)
{
    Projectile* p = new Projectile(this, m_player->GetBox(), target);
    m_projectiles.push_back(std::unique_ptr<Projectile>(p));
}

void Weapon::Render(SDL_Rect &camera)
{
    for (auto& projectile : m_projectiles)
    {
        projectile->Render(camera);
    }

    for (auto &explosion : m_explosions)
    {
        //printf("(%d, %d)\n", explosion->GetPosition().x, explosion->GetPosition().y);
        explosion->Render(camera);
    }
}

void Weapon::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size)
{
    for (unsigned int i = 0; i < m_projectiles.size(); ++i)
    {
        Projectile *projectile = m_projectiles.at(i).get();
        if (projectile != nullptr)
            projectile->Move(time_step, tiles, level_size);
    }
}

void Weapon::DeleteProjectile(Projectile *p)
{
    for (unsigned int i = 0; i < m_projectiles.size(); ++i)
    {
        if (p == this->m_projectiles.at(i).get())
        {
            this->m_projectiles.erase(m_projectiles.begin() + i);
            DPoint pos = p->GetMiddle();
            Explosion* explosion = new Explosion(this, 50, (int)pos.x, (int)pos.y);
            this->m_explosions.push_back(std::unique_ptr<Explosion>(explosion));
        }
    }
}

void Weapon::DeleteExplosion(Explosion *e)
{
    for (unsigned int i = 0; i < m_explosions.size(); ++i)
    {
        if (e == this->m_explosions.at(i).get())
        {
            this->m_explosions.erase(m_explosions.begin() + i);
        }
    }
}
