#include "Humanoid.h"
#include "Map.h"

Humanoid::Humanoid(std::string type, Map *map, PTexture texture)
    : Entity("Humanoid: " + type, texture)
{
    m_map = map;
    m_max_health = 100.f;
    m_health = m_max_health;
    m_health_bar = std::unique_ptr<ProgressBar>(new ProgressBar(static_cast<int>(m_box.w), 5, m_max_health));
}

Humanoid::~Humanoid()
{
}

Tile* Humanoid::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point<int> level_size, std::vector<std::shared_ptr<Humanoid>> humanoids)
{
    double dx = (m_vel.x * time_step);
    m_box.x = wSDL::Constrain(m_box.x + dx, 0, level_size.x - m_box.w);
    Tile* wall_x = this->TouchesWall(tiles);
    if (wall_x != nullptr)
    {
        m_box.x -= dx;
        Point<double> dist = wSDL::Distance(this->m_box, wall_x->GetBox());
        m_box.x += dist.x;
    }

    double dy = (m_vel.y * time_step);
    m_box.y = wSDL::Constrain(m_box.y + dy, 0, level_size.y - m_box.h);
    Tile* wall_y = this->TouchesWall(tiles);
    if (wall_y != nullptr)
    {
        m_box.y -= dy;
        Point<double> dist = wSDL::Distance(this->m_box, wall_y->GetBox());
        m_box.y += dist.y;
    }

    m_health_bar->Update(m_health);

    return wall_x;
}

Map* Humanoid::GetMap()
{
    return m_map;
}

void Humanoid::Render(SDL_Rect &camera)
{
    this->Entity::Render(camera);
    this->m_health_bar->Render(camera, m_box.x, m_box.y);
}

void Humanoid::Damage(double damage)
{
    m_health = wSDL::Constrain(m_health - damage, 0, m_max_health);
}
