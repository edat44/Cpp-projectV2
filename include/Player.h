#ifndef PLAYER_H
#define PLAYER_H

#include "wSDL.h"
#include "Tile.h"
#include "LTexture.h"
#include "LRect.h"
#include "Projectile.h"
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

        static const int S_MAX_VEL = 600;

        void Position(DPoint pos);

        void HandleEvent(SDL_Event &e, SDL_Rect &camera);

        //time_step is measured in seconds
        void Move(double time_step, std::vector<Tile*> tiles, Point level_size);

        void SetCamera(SDL_Rect &camera, Point level_size);

        void Render(SDL_Rect &camera);

        Tile* TouchesWall(std::vector<Tile*> tiles);

        static bool S_SetTexture();
        static void S_Free();

    private:
        static const std::string S_TEXTURE_PATH;
        static LTexture* s_texture;

        static const SDL_Keycode UP = SDLK_w;
        static const SDL_Keycode DOWN = SDLK_s;
        static const SDL_Keycode LEFT = SDLK_a;
        static const SDL_Keycode RIGHT = SDLK_d;

        DRect m_box;
        DPoint m_vel;

        Point m_face_direction;
    
        std::vector<Projectile*> m_projectiles;
};

#endif // PLAYER_H
