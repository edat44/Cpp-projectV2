#include "Player.h"
#include "Map.h"
#include <cmath>

const std::string Player::m_path_texture = "resources/dot_with_arrow.png";

Player::Player()
{
    this->m_box.x = 0.f;
    this->m_box.y = 0.f;
    this->m_box.w = Player::S_WIDTH;
    this->m_box.h = Player::S_HEIGHT;

    this->m_vel.x = 0.f;
    this->m_vel.y = 0.f;

    this->m_face_direction.x = wSDL::SCREEN_WIDTH / 2.0f;
    this->m_face_direction.y = wSDL::SCREEN_HEIGHT / 2.0f;

    this->LoadTexture();
}

void Player::Position(DPoint pos)
{
    this->m_box.x = ((pos.x * Map::TILE_WIDTH) + (Map::TILE_WIDTH / 2) - (Player::S_WIDTH / 2));
    this->m_box.y = ((pos.y * Map::TILE_HEIGHT) + (Map::TILE_HEIGHT / 2) - (Player::S_HEIGHT / 2));
}

Player::~Player()
{
    this->Free();
}

void Player::HandleEvent(SDL_Event &e, SDL_Rect &camera)
{
    if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.repeat == 0)
    {
        int inverted = e.type == SDL_KEYDOWN ? 1 : -1;
        double vel = Player::S_MAX_VEL * inverted * 1.0f;

        switch(e.key.keysym.sym)
        {
        case Player::UP:
            this->m_vel.y -= vel;
            break;

        case Player::DOWN:
            this->m_vel.y += vel;
            break;

        case Player::LEFT:
            this->m_vel.x -= vel;
            break;

        case Player::RIGHT:
            this->m_vel.x += vel;
            break;
        }
    }
    else if (e.type == SDL_MOUSEMOTION)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        this->m_face_direction.x = x;
        this->m_face_direction.y = y;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        this->m_face_direction.x = x;
        this->m_face_direction.y = y;
        m_projectiles.push_back (new Projectile(m_box, Point {camera.x + x, camera.y + y}));
    }
}

void Player::Move(double time_step, std::vector<Tile*> tiles, Point level_size)
{
    //X MOVEMENT
    double dx = (m_vel.x * time_step);
    m_box.x += dx;
    Tile* wall = this->TouchesWall(tiles);
    if (m_box.x < 0 || (m_box.x + Player::S_WIDTH > level_size.x) || wall != nullptr)
    {
        m_box.x -= dx; //Move back
        if (wall != nullptr)
        {
            DPoint dist = wSDL::Distance(this->m_box, wall->GetBox());
            m_box.x += dist.x;
        }
        else if (m_box.x < 0)
            m_box.x = 0;
        else
            m_box.x = level_size.x - Player::S_WIDTH;
    }

    //Y MOVEMENT
    double dy = (m_vel.y * time_step);
    m_box.y += dy;
    wall = this->TouchesWall(tiles);
    if (m_box.y < 0 || (m_box.y + Player::S_HEIGHT > level_size.y) || wall != nullptr)
    {
        m_box.y -= dy; //Move back
        if (wall != nullptr)
        {
            DPoint dist = wSDL::Distance(this->m_box, wall->GetBox());
            m_box.y += dist.y;
        }
        else if (m_box.y < 0)
            m_box.y = 0;
        else
            m_box.y = level_size.y - Player::S_HEIGHT;
    }

    for (Projectile* projectile: m_projectiles)
    {
        projectile->Move(time_step, tiles, level_size);
    }

}

void Player::SetCamera(SDL_Rect &camera, Point level_size)
{
    //Center the camera over the player
    camera.x = (int)(m_box.x + (Player::S_WIDTH / 2)) - (wSDL::SCREEN_WIDTH / 2);
    camera.y = (int)(m_box.y + (Player::S_HEIGHT / 2)) - (wSDL::SCREEN_HEIGHT / 2);

    camera.x = std::min(std::max(camera.x, 0), (level_size.x - camera.w));
    camera.y = std::min(std::max(camera.y, 0), (level_size.y - camera.h));
}

void Player::Render(SDL_Rect &camera)
{
    DPoint start = DPoint{(m_box.x - camera.x + (m_box.w / 2)), (m_box.y - camera.y + (m_box.h / 2))};
    double angle = wSDL::GetAngle(start, m_face_direction);
    this->m_texture->Render((int)m_box.x - camera.x, (int)m_box.y - camera.y, nullptr, angle);

    for (Projectile* projectile: m_projectiles)
    {
        projectile->Render(camera);
    }
}

Tile* Player::TouchesWall(std::vector<Tile*> tiles)
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

bool Player::LoadTexture()
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

void Player::Free()
{
    if (this->m_texture != nullptr)
    {
        this->m_texture->Free();
        delete this->m_texture;
    }
}
