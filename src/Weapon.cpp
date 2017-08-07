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
    Projectile* p = new Projectile(m_player->GetBox(), target);
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
        explosion->Render(camera);
    }
}

void Weapon::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size)
{
    for (unsigned int i = 0; i < m_projectiles.size(); ++i)
    {
        Projectile *projectile = m_projectiles.at(i).get();
        projectile->Move(time_step, tiles, level_size);
        if (!projectile->Update(tiles))
            DeleteProjectile(i);
    }

    for (unsigned int i = 0; i < m_explosions.size(); ++i)
    {
        if (!m_explosions.at(i)->Update())
        {
            m_explosions.erase(m_explosions.begin() + i);
        }
    }
}

void Weapon::DeleteProjectile(unsigned int index)
{
    DPoint pos = m_projectiles.at(index)->GetMiddle();
    this->m_projectiles.erase(m_projectiles.begin() + index);
    Explosion *explosion = new Explosion(15, (int)pos.x, (int)pos.y);
    this->m_explosions.push_back(std::unique_ptr<Explosion>(explosion));
}
