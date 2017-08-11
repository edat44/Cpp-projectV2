#ifndef HUMANOID_H
#define HUMANOID_H

#include "Entity.h"
#include <string>
#include <memory>

class Map;

class Humanoid : public Entity
{
    public:
        Humanoid(std::string type, Map* map, PTexture texture);
        virtual ~Humanoid();

        virtual Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point<int> level_size) = 0;

        Map* GetMap();

    protected:
        Map *m_map;
    private:
};

#endif // HUMANOID_H
