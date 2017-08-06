#ifndef WEAPON_H
#define WEAPON_H

#include "wSDL.h"
#include "Tile.h"
#include "Projectile.h"
#include <vector>

class Player;

class Weapon
{
    public:
        Weapon(Player* player);
        virtual ~Weapon();

        void Fire(Point target);

        void Render(SDL_Rect &camera);

        void Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size);

        void DeleteProjectile(Projectile *p);

    protected:
    private:
        std::vector<std::unique_ptr<Projectile>> m_projectiles;
        std::vector<PSprite> m_explosions;
        Player* m_player;
};

#endif // WEAPON_H
