#include "Entity.h"
#include "Map.h"

Entity::Entity(std::string type, std::string path_texture)
{
    this->m_type = type;
    this->m_path_texture = path_texture;
    this->LoadTexture();

    this->m_box.x = 0.f;
    this->m_box.y = 0.f;

    this->m_vel.x = 0.f;
    this->m_vel.y = 0.f;

    this->m_angle = 0.f;
}

Entity::~Entity()
{
}

bool Entity::LoadTexture()
{
    bool success = true;
    this->m_texture = std::make_shared<LTexture>();
    if (!this->m_texture->LoadFromFile(this->m_path_texture))
    {
        printf("Could not load texture %s!\n", this->m_path_texture.c_str());
        success = false;
    }

    this->m_box.w = m_texture->GetWidth();
    this->m_box.h = m_texture->GetHeight();

    return success;
}

void Entity::Position(DPoint pos)
{
    this->m_box.x = ((pos.x * Map::TILE_WIDTH) + (Map::TILE_WIDTH / 2) - (m_box.w / 2));
    this->m_box.y = ((pos.y * Map::TILE_HEIGHT) + (Map::TILE_HEIGHT / 2) - (m_box.h / 2));
}

Tile* Entity::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size)
{
    double dx = (m_vel.x * time_step);
    double dy = (m_vel.y * time_step);
    m_box.x = wSDL::Constrain(m_box.x + dx, 0, level_size.x - m_box.w);
    m_box.y = wSDL::Constrain(m_box.y + dy, 0, level_size.y - m_box.h);
    Tile* wall = this->TouchesWall(tiles);
    if (wall != nullptr)
    {
        m_box.x -= dx;
        m_box.y -= dy;
        DPoint dist = wSDL::Distance(this->m_box, wall->GetBox());
        m_box.x += dist.x;
        m_box.y += dist.y;
    }
    return wall;
}

void Entity::Render(SDL_Rect &camera)
{
    if (wSDL::CheckCollision(this->m_box, camera))
    {
        this->m_texture->Render((int)m_box.x - camera.x, (int)m_box.y - camera.y, nullptr, m_angle);

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
