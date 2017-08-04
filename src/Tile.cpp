#include "Tile.h"
#include "Map.h"

Tile::Tile(int x, int y, int tile_type, LTexture *texture, std::vector<SDL_Rect> *clips)
{
    this->m_box.x = x;
    this->m_box.y = y;
    this->m_box.w = Map::TILE_WIDTH;
    this->m_box.h = Map::TILE_HEIGHT;

    this->m_type = tile_type;

    this->m_texture = texture;

    this->m_tile_clips = *clips;
}

void Tile::Render(SDL_Rect &camera)
{
    //if tile is on the screen
    if (wSDL::CheckCollision(camera, this->m_box))
    {
        this->m_texture->Render(this->m_box.x - camera.x, this->m_box.y - camera.y, &this->m_tile_clips.at(this->m_type));
    }
}

int Tile::GetType()
{
    return this->m_type;
}

SDL_Rect Tile::GetBox()
{
    return this->m_box;
}
