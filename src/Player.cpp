#include "Player.h"

const std::string Player::S_TEXTURE_PATH = "resources/dot.bmp";
LTexture* Player::s_texture = nullptr;

Player::Player()
{
    this->m_box.x = 0;
    this->m_box.y = 0;
    this->m_box.w = Player::S_WIDTH;
    this->m_box.h = Player::S_HEIGHT;

    this->m_vel.x = 0;
    this->m_vel.y = 0;
}

void Player::Position(Point pos)
{
    this->m_box.x = (int)((pos.x* Tile::S_WIDTH) + (Tile::S_WIDTH / 2) - (Player::S_WIDTH / 2));
    this->m_box.y = (int)((pos.y* Tile::S_HEIGHT) + (Tile::S_HEIGHT / 2) - (Player::S_HEIGHT / 2));
}

Player::~Player()
{

}

void Player::HandleEvent(SDL_Event &e)
{
    if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.repeat == 0)
    {
        int inverted = e.type == SDL_KEYDOWN ? 1 : -1;
        int vel = Player::S_MAX_VEL * inverted;

        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            this->m_vel.y -= vel;
            break;
        case SDLK_DOWN:
            this->m_vel.y += vel;
            break;
        case SDLK_LEFT:
            this->m_vel.x -= vel;
            break;
        case SDLK_RIGHT:
            this->m_vel.x += vel;
            break;
        }
    }
}

void Player::Move(std::vector<Tile*> tiles, Point level_size)
{
    bool wall_touch = this->TouchesWall(tiles);
        //X MOVEMENT
    m_box.x += m_vel.x;
    if (m_box.x < 0 || (m_box.x + Player::S_WIDTH > level_size.x) || wall_touch)
        m_box.x -= m_vel.x; //Move back

    //Y MOVEMENT
    m_box.y += m_vel.y;
    if (m_box.y < 0 || (m_box.y + Player::S_HEIGHT > level_size.y) || wall_touch)
        m_box.y -= m_vel.y; //Move back
}

void Player::SetCamera(SDL_Rect &camera, Point level_size)
{
    //Center the camera over the player
    camera.x = (m_box.x + (Player::S_WIDTH / 2)) - (wSDL::SCREEN_WIDTH / 2);
    camera.y = (m_box.y + (Player::S_HEIGHT / 2)) - (wSDL::SCREEN_HEIGHT / 2);

    camera.x = std::min(std::max(camera.x, 0), (level_size.x - camera.w));
    camera.y = std::min(std::max(camera.y, 0), (level_size.y - camera.h));
}

void Player::Render(SDL_Rect &camera)
{
    Player::s_texture->Render(m_box.x - camera.x, m_box.y - camera.y);
}

bool Player::TouchesWall(std::vector<Tile*> tiles)
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
            if (wSDL::CheckCollision(m_box, tile->GetBox()))
                return true;
        }
    }

    return false;
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
