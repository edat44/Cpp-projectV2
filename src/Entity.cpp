#include "Entity.h"
#include "Map.h"

Entity::Entity(std::string type, PTexture texture)
{
    this->m_type = type;
    this->m_texture = texture;

    this->m_box.w = m_texture->GetWidth();
    this->m_box.h = m_texture->GetHeight();

    this->m_box.x = 0.f;
    this->m_box.y = 0.f;

    this->m_vel.x = 0.f;
    this->m_vel.y = 0.f;

    this->m_angle = 0.f;
}

Entity::~Entity()
{
}

void Entity::SetPosition(DPoint pos)
{
    this->m_box.x = ((pos.x * Map::TILE_WIDTH) + (Map::TILE_WIDTH / 2) - (m_box.w / 2));
    this->m_box.y = ((pos.y * Map::TILE_HEIGHT) + (Map::TILE_HEIGHT / 2) - (m_box.h / 2));
}

void Entity::Render(SDL_Rect &camera)
{
    if (wSDL::CheckCollision(this->m_box, camera))
    {
        this->m_texture->Render(camera, (int)m_box.x, (int)m_box.y, nullptr, m_angle);

    }
}

Tile* Entity::TouchesWall(std::vector<std::shared_ptr<Tile>> tiles)
{
    for (std::shared_ptr<Tile> tile : tiles)
    {
        switch(tile->GetType())
        {
            case Map::TILE_BLUE:
            case Map::TILE_RED:
            case Map::TILE_GREEN:
                break;
            default:
                if (wSDL::CheckCollision(this->m_box, tile->GetBox()))
                {
                    return tile.get();
                }
        }
    }
    return nullptr;
}

DRect Entity::GetBox()
{
    return m_box;
}

DPoint Entity::GetPosition()
{
    return DPoint{m_box.x, m_box.y};
}

DPoint Entity::GetMiddle()
{
    return DPoint{m_box.x + m_box.w / 2, m_box.y + m_box.h / 2};
}
