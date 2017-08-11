#ifndef PLAYER_H
#define PLAYER_H

#include "wSDL.h"
#include "Tile.h"
#include "Humanoid.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include "Weapon.h"

class Map;

class Player : public Humanoid
{
    public:
        Player(Map *map);
        virtual ~Player();

        static const int S_MAX_VEL = 250;

        void HandleEvent(SDL_Event &e, SDL_Rect &camera);

        virtual void Render(SDL_Rect &camera);

        //time_step is measured in seconds
        virtual Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point<int> level_size, std::vector<std::shared_ptr<Humanoid>> humanoids);

        void SetCamera(SDL_Rect &camera, Point<int> level_size);

    private:

        static const SDL_Keycode UP = SDLK_w;
        static const SDL_Keycode DOWN = SDLK_s;
        static const SDL_Keycode LEFT = SDLK_a;
        static const SDL_Keycode RIGHT = SDLK_d;

        Point<int> m_face_direction;

        std::shared_ptr<Weapon> m_weapon;
};

#endif // PLAYER_H
