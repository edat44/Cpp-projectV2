#ifndef TILE_H
#define TILE_H

#include <LTexture.h>
#include <string>

class Tile
{
    public:
        Tile(int x, int y, int tile_type);

        void Render(camera_t* camera);

        int GetType();

        SDL_Rect GetBox();

        static int GetWidth();
        static int GetHeight();

    private:
        static const std::string TEXTURE_PATH;
        static LTexture* s_tile_texture;
        static bool SetTexture();

        SDL_Rect m_box;

        int m_type;
};

#endif // TILE_H
