#include "Tile.h"
#include "Map.h"

Tile::Tile(int x, int y, int tile_type, PTexture texture)
{
    this->m_box.x = x;
    this->m_box.y = y;
    this->m_box.w = Map::TILE_WIDTH;
    this->m_box.h = Map::TILE_HEIGHT;

    this->m_type = tile_type;

    this->m_sprite = texture->MakeSprite(tile_type, 0, LSprite::SPRITE_STATIC);
}

void Tile::Render(SDL_Rect &camera)
{
    //if tile is on the screen
    //if (wSDL::CheckCollision(camera, this->m_box))
    {
        this->m_sprite->Render(camera, this->m_box.x, this->m_box.y);
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
