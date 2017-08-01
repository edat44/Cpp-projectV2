#include "Tile.h"

LTexture* Tile::s_tile_texture = nullptr;
const std::string Tile::TEXTURE_PATH = "resources/tiles.png";

Tile::Tile(int x, int y, int tile_type)
{
    if (Tile::s_tile_texture == nullptr)
    {
        Tile::SetTexture();
    }
    this->m_box.x = x;
    this->m_box.y = y;
    this->m_box.w = 80;
    this->m_box.h = 80;
}

bool Tile::SetTexture()
{

}
