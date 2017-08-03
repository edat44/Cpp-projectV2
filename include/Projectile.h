#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Tile.h"
#include "LTexture.h"
#include <string>

class Projectile
{
public:
    Projectile();
    virtual ~Projectile();
    
    static const int S_WIDTH = 5;
    static const int S_HEIGHT = 5;
    
    static const int S_MAX_VEL = 5;
    
    void Move(std::vector<Tile*> tiles, Point level_size);
    
    
    
private:
    static const std::string S_TEXTURE_PATH;
    static LTexture* s_texture;

};

#endif // PROJECTILE_H
