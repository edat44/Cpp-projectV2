#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Tile.h"
#include "LTexture.h"
#include <string>

class Projectile
{
public:
    Projectile(DPoint start, Point target);
    virtual ~Projectile();

    static const int S_WIDTH = 5;
    static const int S_HEIGHT = 5;

    static const int S_MAX_VEL = 500.f;

    void Move(double time_step, std::vector<Tile*> tiles, Point level_size);

    void Render(SDL_Rect &camera);

    static bool S_SetTexture();
    static void S_Free();

private:
    static const std::string S_TEXTURE_PATH;
    static LTexture* s_texture;

    DRect m_box;
    DPoint m_vel;

    Point m_target;

    double m_angle;

};

#endif // PROJECTILE_H
