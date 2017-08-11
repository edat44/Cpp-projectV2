#ifndef TILE_H
#define TILE_H

#include "LSprite.h"
#include "LTexture.h"
#include "wSDL.h"
#include <vector>
#include <memory>
#include <string>
#include "LSprite.h"

class Tile : public LSprite
{
    public:
        Tile(int x, int y, int tile_type, PTexture texture, std::string meta_data_key = "");

        void Render(SDL_Rect &camera);

        int GetType();

        void Shift(int x, int y);

    private:

        int m_type;

        std::string m_meta_data_key;
};

#endif // TILE_H
