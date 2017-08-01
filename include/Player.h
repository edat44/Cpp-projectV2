#ifndef PLAYER_H
#define PLAYER_H

#include "wSDL.h"

class Player
{
    public:
        Player();
        virtual ~Player();

        static const int WIDTH = 20;
        static const int HEIGHT = 20;

        static const int MAX_VEL = 5;

        void HandleEvent(SDL_Event &e);
};

#endif // PLAYER_H
