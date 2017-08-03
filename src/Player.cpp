#include "Player.h"
#include <cmath>
#define PI 3.14159265

const std::string Player::S_TEXTURE_PATH = "resources/dot_with_arrow.png";
LTexture* Player::s_texture = nullptr;

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
}

void Player::Position(DPoint pos)
{
    this->m_box.x = ((pos.x * Tile::S_WIDTH) + (Tile::S_WIDTH / 2) - (Player::S_WIDTH / 2));
    this->m_box.y = ((pos.y * Tile::S_HEIGHT) + (Tile::S_HEIGHT / 2) - (Player::S_HEIGHT / 2));
}

Player::~Player()
{

}

void Player::HandleEvent(SDL_Event &e)
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
    else if (e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
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
    double angle = 0.0;
    double x = fabs(m_box.x - camera.x + (m_box.w / 2));
    double y = fabs(m_box.y - camera.y + (m_box.h / 2));
    double dx = m_face_direction.x - x;
    double dy = m_face_direction.y - y;
    if (dx == 0.0)
        angle = 90.0;
    else
        angle = atan(fabs(dy) / fabs(dx)) * 180.0 / PI;

    if (m_face_direction.x <= x && m_face_direction.y >= y)       //Q4 (topright)
        angle = 180.0 - angle;
    else if (m_face_direction.x < x && m_face_direction.y < y)  //Q1 (bottomright)
        angle += 180.0;
    else if (m_face_direction.x >= x && m_face_direction.y <= y)  //Q2 (bottomleft)
        angle = -angle;
    else                                                        //Q3 (topleft)
        angle = angle;

    Player::s_texture->Render((int)m_box.x - camera.x, (int)m_box.y - camera.y, nullptr, angle);

}

Tile* Player::TouchesWall(std::vector<Tile*> tiles)
{
    for (Tile* tile : tiles)
    {
        switch(tile->GetType())
        {
        case Tile::BLUE:
        case Tile::RED:
        case Tile::GREEN:
            break;
        default:
            if (wSDL::CheckCollision(this->m_box, tile->GetBox()))
                return tile;
        }
    }

    return nullptr;
}

bool Player::S_SetTexture()
{
    bool success = true;
    Player::s_texture = new LTexture();
    if (!Player::s_texture->LoadFromFile(Player::S_TEXTURE_PATH))
    {
        printf("Could not load player texture!\n");
        success = false;
    }

    return success;
}

void Player::S_Free()
{
    Player::s_texture->Free();
    delete Player::s_texture;
}
