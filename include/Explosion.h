#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "LSprite.h"

class Weapon;

class Explosion : public LSprite
{
    public:
        Explosion(int frame_time, int x, int y);
        virtual ~Explosion();

    protected:

    private:
};

#endif // EXPLOSION_H
