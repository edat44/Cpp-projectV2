#ifndef TILE_H
#define TILE_H

#include <LTexture.h>
#include <string>
#include "wSDL.h"
#include <vector>

class Tile
{
    public:
        Tile(int x, int y, int tile_type);

        void Render(SDL_Rect &camera);

        int GetType();

        SDL_Rect GetBox();

        static const int S_WIDTH = 80;
        static const int S_HEIGHT = 80;

        /*
            0 is the top left corner of the spritesheet, working down, then to the right
        */
        static const int RED = 0;
        static const int GREEN = 1;
        static const int BLUE = 2;
        static const int CENTER = 3;
        static const int TOP = 4;
        static const int TOPRIGHT = 5;
        static const int RIGHT = 6;
        static const int BOTTOMRIGHT = 7;
        static const int BOTTOM = 8;
        static const int BOTTOMLEFT = 9;
        static const int LEFT = 10;
        static const int TOPLEFT = 11;

        static const int TOTAL_TILE_SPRITES = 12;

        static bool S_SetTexture();
        static void S_Free();

    private:
        static const std::string S_TEXTURE_PATH;
        static const int S_TOTAL_TILE_SPRITE_ROWS = 3;
        static const int S_TOTAL_TILE_SPRITE_COLS = 4;
        static const int S_TOTAL_TILE_SPRITES = S_TOTAL_TILE_SPRITE_ROWS * S_TOTAL_TILE_SPRITE_COLS;

        static LTexture* s_tile_texture;
        static std::vector<SDL_Rect> s_tile_clips;

        SDL_Rect m_box;

        int m_type;
};

#endif // TILE_H
