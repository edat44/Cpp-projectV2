#include "Humanoid.h"
#include "Map.h"

Humanoid::Humanoid(std::string type, PTexture texture, Map *map)
    : Entity("Humanoid: " + type, texture)
{
    m_map = map;
}

Humanoid::~Humanoid()
{
}

Tile* Humanoid::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size)
{
    double dx = (m_vel.x * time_step);
    m_box.x = wSDL::Constrain(m_box.x + dx, 0, level_size.x - m_box.w);
    Tile* wall_x = this->TouchesWall(tiles);
    if (wall_x != nullptr)
    {
        m_box.x -= dx;
        DPoint dist = wSDL::Distance(this->m_box, wall_x->GetBox());
        m_box.x += dist.x;
    }

    double dy = (m_vel.y * time_step);
    m_box.y = wSDL::Constrain(m_box.y + dy, 0, level_size.y - m_box.h);
    Tile* wall_y = this->TouchesWall(tiles);
    if (wall_y != nullptr)
    {
        m_box.y -= dy;
        DPoint dist = wSDL::Distance(this->m_box, wall_y->GetBox());
        m_box.y += dist.y;
    }

    return wall_x;
}

void Humanoid::Render(SDL_Rect &camera)
{
    this->Entity::Render(camera);
}
