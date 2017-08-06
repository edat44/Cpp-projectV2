#ifndef PLAYER_H
#define PLAYER_H

#include "wSDL.h"
#include "Tile.h"
#include "Projectile.h"
#include "Humanoid.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

class Player : public Humanoid
{
    public:
        Player();
        virtual ~Player();

        static const int S_WIDTH = 20;
        static const int S_HEIGHT = 20;

        static const int S_MAX_VEL = 150;

        void HandleEvent(SDL_Event &e, SDL_Rect &camera);

        virtual void Render(SDL_Rect &camera);

        //time_step is measured in seconds
        virtual Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size);

        void SetCamera(SDL_Rect &camera, Point level_size);

    private:

        static const SDL_Keycode UP = SDLK_w;
        static const SDL_Keycode DOWN = SDLK_s;
        static const SDL_Keycode LEFT = SDLK_a;
        static const SDL_Keycode RIGHT = SDLK_d;

        Point m_face_direction;

        std::vector<std::unique_ptr<Projectile>> m_projectiles;

        std::vector<PSprite> m_explosions;
};

#endif // PLAYER_H
