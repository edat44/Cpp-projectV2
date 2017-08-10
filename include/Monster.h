#ifndef MONSTER_H
#define MONSTER_H

#include "wSDL.h"
#include "Tile.h"
#include "Humanoid.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

class Monster : public Humanoid
{
    public:
        Monster(Map *map);
        virtual ~Monster();
    
        static const int S_MAX_VEL = 200;
    
        virtual void Render(SDL_Rect &camera);
    
        virtual Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size);
        
    private:
};

#endif // MONSTER_H
