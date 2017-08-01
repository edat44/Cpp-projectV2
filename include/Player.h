#ifndef PLAYER_H
#define PLAYER_H

#include "wSDL.h"
#include "Tile.h"
#include <vector>
#include <algorithm>
#include <string>

class Player
{
    public:
        Player();
        virtual ~Player();

        static const int S_WIDTH = 20;
        static const int S_HEIGHT = 20;

        static const int S_MAX_VEL = 5;

        void HandleEvent(SDL_Event &e);

        void Move(std::vector<Tile*> tiles, Point level_size);

        void SetCamera(SDL_Rect &camera, Point level_size);

        void Render(SDL_Rect &camera);

        bool TouchesWall(std::vector<Tile*> tiles);

        static bool S_SetTexture();
        static void S_Free();

    private:
        static const std::string S_TEXTURE_PATH;
        static LTexture* s_texture;

        SDL_Rect m_box;

        Point m_vel;
};

#endif // PLAYER_H
