#ifndef TILE_H
#define TILE_H

#include "LTexture.h"
#include <string>
#include "wSDL.h"
#include <vector>
#include <memory>

class Tile
{
    public:
        Tile(int x, int y, int tile_type, std::shared_ptr<LTexture> texture, std::vector<SDL_Rect> *clips);

        void Render(SDL_Rect &camera);

        int GetType();

        SDL_Rect GetBox();

    private:

        std::vector<SDL_Rect> m_tile_clips;
        std::shared_ptr<LTexture> m_texture;

        SDL_Rect m_box;

        int m_type;
};

#endif // TILE_H
