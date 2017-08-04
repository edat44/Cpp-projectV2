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
    this->Free();
}

bool Entity::LoadTexture()
{
    bool success = true;
    this->m_texture = new LTexture();
    if (!this->m_texture->LoadFromFile(this->m_path_texture))
    {
        printf("Could not load texture %s!\n", this->m_path_texture.c_str());
        success = false;
    }

    this->m_box.w = m_texture->GetWidth();
    this->m_box.h = m_texture->GetHeight();

    return success;
}

void Entity::Move(double time_step, std::vector<Tile*> tiles, Point level_size)
{
    double dx = (m_vel.x * time_step);
    m_box.x += dx;
    Tile* wall = this->TouchesWall(tiles);
    if (m_box.x < 0 || (m_box.x + m_box.w > level_size.x) || wall != nullptr)
    {
        m_box.x -= dx;
        if (wall != nullptr)
        {
            DPoint dist = wSDL::Distance(this->m_box, wall->GetBox());
            m_box.x += dist.x;
        }
        else if (m_box.x < 0)
            m_box.x = 0;
        else
            m_box.x = level_size.x - m_box.w;
    }

    double dy = (m_vel.y * time_step);
    m_box.y += dy;
    wall = this->TouchesWall(tiles);
    if (m_box.y < 0 || (m_box.y + m_box.h > level_size.y) || wall != nullptr)
    {
        m_box.y -= dy;
        if (wall != nullptr)
        {
            DPoint dist = wSDL::Distance(this->m_box, wall->GetBox());
            m_box.y += dist.y;
        }
        else if (m_box.y < 0)
            m_box.y = 0;
        else
            m_box.y = level_size.y - m_box.h;
    }
}

void Entity::Render(SDL_Rect &camera)
{
    if (wSDL::CheckCollision(this->m_box, camera))
    {
        this->m_texture->Render((int)m_box.x - camera.x, (int)m_box.y - camera.y, nullptr, m_angle);

    }
}

Tile* Entity::TouchesWall(std::vector<Tile*> tiles)
{
    for (Tile* tile : tiles)
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
                    return tile;
                }
        }
    }
    return nullptr;
}

void Entity::Free()
{
    if (this->m_texture != nullptr)
    {
        this->m_texture->Free();
        delete this->m_texture;
    }
}
