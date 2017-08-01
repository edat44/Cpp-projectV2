#include "Tile.h"

const std::string Tile::S_TEXTURE_PATH = "resources/tiles.png";

LTexture* Tile::s_tile_texture = nullptr;
std::vector<SDL_Rect> Tile::s_tile_clips = {};

Tile::Tile(int x, int y, int tile_type)
{
    this->m_box.x = x;
    this->m_box.y = y;
    this->m_box.w = Tile::S_WIDTH;
    this->m_box.h = Tile::S_HEIGHT;

    this->m_type = tile_type;
}

void Tile::Render(SDL_Rect &camera)
{
    //if tile is on the screen
    if (wSDL::CheckCollision(camera, this->m_box))
    {
        Tile::s_tile_texture->Render(this->m_box.x - camera.x, this->m_box.y - camera.y, &Tile::s_tile_clips.at(this->m_type));
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

bool Tile::S_SetTexture()
{
    bool success = true;
    Tile::s_tile_texture = new LTexture();
    if (!Tile::s_tile_texture->LoadFromFile(S_TEXTURE_PATH))
    {
        printf("Failed to load tile texture\n");
        success = false;
    }
    for (int y = 0; y < Tile::S_TOTAL_TILE_SPRITE_ROWS; ++y)
    {
        for (int x = 0; x < Tile::S_TOTAL_TILE_SPRITE_COLS; ++x)
        {
            Tile::s_tile_clips.push_back({x * Tile::S_WIDTH, y * Tile::S_HEIGHT, Tile::S_WIDTH, Tile::S_HEIGHT});
        }
    }

    return success;
}

void Tile::S_Free()
{
    delete Tile::s_tile_texture;
    Tile::s_tile_texture->Free();
}
