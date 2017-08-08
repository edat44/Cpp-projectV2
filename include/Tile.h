#ifndef TILE_H
#define TILE_H

#include "LSprite.h"
#include "LTexture.h"
#include "wSDL.h"
#include <vector>
#include <memory>
#include <string>

class Tile
{
    public:
        Tile(int x, int y, int tile_type, PTexture texture);

        void Render(SDL_Rect &camera);

        int GetType();

        SDL_Rect GetBox();

        void Shift(int x, int y);

    private:
        PSprite m_sprite;

        SDL_Rect m_box;

        int m_type;
};

#endif // TILE_H
