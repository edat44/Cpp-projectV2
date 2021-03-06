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

        virtual Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point<int> level_size, std::vector<std::shared_ptr<Humanoid>> humanoids) = 0;

        Map* GetMap();

        virtual void Render(SDL_Rect &camera);

    protected:
        Map *m_map;
    private:
};

#endif // HUMANOID_H
