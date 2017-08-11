#ifndef WEAPON_H
#define WEAPON_H

#include "wSDL.h"
#include "Tile.h"
#include "Projectile.h"
#include "Explosion.h"
#include "LTimer.h"
#include <vector>

class Player; class Map;

class Weapon
{
    public:
        Weapon(Player* player, double fire_rate = 0);
        virtual ~Weapon();

        void Fire(Point<int> target);

        void Render(SDL_Rect &camera);

        void Update(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point<int> level_size);

        void DeleteProjectile(Projectile *proj);
        void DeleteExplosion(Explosion *exp);

        Map* GetMap();

    protected:

    private:
        std::vector<std::unique_ptr<Projectile>> m_projectiles;
        std::vector<std::unique_ptr<Explosion>> m_explosions;

        double m_fire_rate; //Bullets per second
        std::unique_ptr<LTimer> m_fire_timer;
        Player* m_player;
};

#endif // WEAPON_H
