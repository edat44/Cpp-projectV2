#include "Player.h"
#include "Map.h"
#include <cmath>

Player::Player()
    : Humanoid("Humanoid", wResources::texture_player)
{

    this->m_vel.x = 0.f;
    this->m_vel.y = 0.f;

    this->m_face_direction.x = wSDL::SCREEN_WIDTH / 2.0f;
    this->m_face_direction.y = wSDL::SCREEN_HEIGHT / 2.0f;

    this->m_weapon = std::make_shared<Weapon>(this, 10);
}

Player::~Player()
{

}

void Player::HandleEvent(SDL_Event &e, SDL_Rect &camera)
{
    SDL_GetMouseState(&m_face_direction.x, &m_face_direction.y);
    this->m_angle = wSDL::GetAngle(DPoint{m_box.x + (m_box.w/2) - camera.x, m_box.y + (m_box.h / 2) - camera.y}, m_face_direction);
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
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            m_weapon->Fire(Point{camera.x + m_face_direction.x, camera.y + m_face_direction.y});
        }
    }
}

void Player::Render(SDL_Rect &camera)
{
    this->Entity::Render(camera);
    m_weapon->Render(camera);
}

Tile* Player::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size)
{
    Tile* tile = this->Humanoid::Move(time_step, tiles, level_size);
    m_weapon->Update(time_step, tiles, level_size);
    return tile;
}

void Player::SetCamera(SDL_Rect &camera, Point level_size)
{
    //Center the camera over the player
    camera.x = (int)(m_box.x + (m_box.w / 2)) - (wSDL::SCREEN_WIDTH / 2);
    camera.y = (int)(m_box.y + (m_box.h / 2)) - (wSDL::SCREEN_HEIGHT / 2);

    camera.x = std::min(std::max(camera.x, 0), (level_size.x - camera.w));
    camera.y = std::min(std::max(camera.y, 0), (level_size.y - camera.h));
}
