#include "Tile.h"
#include "Map.h"

Tile::Tile(int x, int y, int tile_type, PTexture texture, std::string meta_data_key)
    : LSprite(*texture, tile_type, 0, LSprite::SPRITE_STATIC)
{
    SetPosition(x, y, false);
    this->m_type = tile_type;
    this->m_meta_data_key = meta_data_key;
}

void Tile::Render(SDL_Rect &camera)
{
    this->LSprite::Render(camera);
}

int Tile::GetType()
{
    return this->m_type;
}

void Tile::Shift(int x, int y)
{
    m_box.x += (m_box.w * x);
    m_box.y += (m_box.h * y);
}
