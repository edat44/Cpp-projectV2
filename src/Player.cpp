#include "Player.h"
#include "Map.h"
#include <cmath>

Player::Player()
    : Humanoid("Humanoid", "resources/dot_with_arrow.png")
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

Player::~Player()
{
    this->m_projectiles.erase(this->m_projectiles.begin(), this->m_projectiles.end());
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
    else if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        this->m_face_direction.x = x;
        this->m_face_direction.y = y;
        this->m_angle = wSDL::GetAngle(DPoint{m_box.x + (m_box.w/2) - camera.x, m_box.y + (m_box.h / 2) - camera.y}, m_face_direction);
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            m_projectiles.push_back(std::unique_ptr<Projectile>(new Projectile(m_box, Point {camera.x + x, camera.y + y}, [this](Projectile* p)
                {
                    for (unsigned int i = 0; i < m_projectiles.size(); ++i)
                    {
                        if (p == this->m_projectiles.at(i).get())
                            this->m_projectiles.erase(m_projectiles.begin() + i);
                    }
                }
            )));
        }
    }
}

void Player::Render(SDL_Rect &camera)
{
    this->Entity::Render(camera);
    for (auto& projectile : m_projectiles)
    {
        projectile->Render(camera);
    }
}

Tile* Player::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size)
{

    Tile* tile = this->Humanoid::Move(time_step, tiles, level_size);

    for (unsigned int i = 0; i < m_projectiles.size(); ++i)
    {
        Projectile *projectile = m_projectiles.at(i).get();
        projectile->Move(time_step, tiles, level_size);
    }
    return tile;
}

void Player::SetCamera(SDL_Rect &camera, Point level_size)
{
    //Center the camera over the player
    camera.x = (int)(m_box.x + (Player::S_WIDTH / 2)) - (wSDL::SCREEN_WIDTH / 2);
    camera.y = (int)(m_box.y + (Player::S_HEIGHT / 2)) - (wSDL::SCREEN_HEIGHT / 2);

    camera.x = std::min(std::max(camera.x, 0), (level_size.x - camera.w));
    camera.y = std::min(std::max(camera.y, 0), (level_size.y - camera.h));
}
