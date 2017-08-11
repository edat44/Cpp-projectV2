#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "LSprite.h"

class Weapon;

class Explosion : public LSprite
{
    public:
        Explosion(Weapon *weapon, int frame_time, int x, int y);
        virtual ~Explosion();

        bool Update();

    protected:
    private:
        Weapon *m_weapon;
};

#endif // EXPLOSION_H
