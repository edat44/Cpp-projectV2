#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Tile.h"
#include "Entity.h"
#include "LTexture.h"
#include "LSound.h"
#include "wSDL.h"
#include <string>
#include <memory>

class Weapon;

class Projectile: public Entity
{
    public:
        Projectile(DPoint start, Point target);
        Projectile(DRect start, Point target);
        virtual ~Projectile();

        static const int WIDTH = 6;
        static const int HEIGHT = 6;

        static const int MAX_VEL = 200.f;

        Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size);

        bool operator==(const Projectile &p);

        bool Done();

    protected:
        Point m_target;

        PSound m_sound_spawn;

        bool m_done;

        void LoadSounds();

};

#endif // PROJECTILE_H
