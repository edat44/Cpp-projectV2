#ifndef HUMANOID_H
#define HUMANOID_H

#include "Entity.h"
#include <string>
#include <memory>

class Map;

class Humanoid : public Entity
{
    public:
        Humanoid(std::string type, PTexture texture, Map *map);
        virtual ~Humanoid();

        virtual Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size) = 0;

    protected:
        virtual void Render(SDL_Rect &camera);
    
        Map *m_map;

    private:
};

#endif // HUMANOID_H
