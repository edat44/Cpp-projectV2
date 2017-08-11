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
        Projectile(Weapon *weapon, double speed, Point<double> start, Point<int> target);
        Projectile(Weapon *weapon, double speed, Rect<double> start, Point<int> target);
        virtual ~Projectile();

        static const int WIDTH = 6;
        static const int HEIGHT = 6;

        Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point<int> level_size, std::vector<std::shared_ptr<Humanoid>> humanoids);

        bool operator==(const Projectile &p);

    protected:
        Point<int> m_target;

        PSound m_sound_spawn;

        uint32_t m_spawn_time;

        Weapon *m_weapon;

        double m_speed;

        void LoadSounds();

};

#endif // PROJECTILE_H
