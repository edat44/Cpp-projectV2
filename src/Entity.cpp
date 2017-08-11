#include "Entity.h"
#include "Map.h"

Entity::Entity(std::string type, PTexture texture)
{
    this->m_type = type;
    this->m_texture = texture;

    Point<int> tex_size = m_texture->GetSize();
    SetSize(tex_size.x, tex_size.y);

    this->m_vel.x = 0.f;
    this->m_vel.y = 0.f;

    this->m_angle = 0.f;
}

Entity::~Entity()
{
}
void Entity::Render(SDL_Rect &camera)
{
    if (wSDL::CheckCollision(this->m_box, wSDL::SDL_RectToIntRect(camera)))
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
