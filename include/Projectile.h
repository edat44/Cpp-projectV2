#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Tile.h"
#include "Entity.h"
#include "LTexture.h"
#include <string>

class Projectile: public Entity
{
    public:
        Projectile(DPoint start, Point target);
        Projectile(DRect start, Point target);
        virtual ~Projectile();
        
        static const int WIDTH = 6;
        static const int HEIGHT = 6;
        
        static const int MAX_VEL = 500.f;

        void Move(double time_step, std::vector<Tile*> tiles, Point level_size);

        bool LoadTexture();
        void Free();

    private:
        static const std::string m_path_texture;
        LTexture* m_texture;

        DRect m_box;
        DPoint m_vel;

        Point m_target;

        double m_angle;

};

#endif // PROJECTILE_H
