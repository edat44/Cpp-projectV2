#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Tile.h"
#include "Entity.h"
#include "LTexture.h"
#include "LSound.h"
#include <string>
#include <memory>

class Projectile: public Entity
{
    public:
        Projectile(DPoint start, Point target);
        Projectile(DRect start, Point target);
        virtual ~Projectile();

        static const int WIDTH = 6;
        static const int HEIGHT = 6;

        static const int MAX_VEL = 600.f;

        Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size);

    protected:
        Point m_target;

        std::shared_ptr<LSound> m_sound_spawn;
        std::shared_ptr<LSound> m_sound_wall;

        void LoadSounds();

};

#endif // PROJECTILE_H
