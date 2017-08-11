#ifndef ENTITY_H
#define ENTITY_H

#include "Tile.h"
#include "LTexture.h"
#include "wResources.h"
#include <vector>
#include <string>
#include <memory>
#include "Box.h"

class Humanoid;

class Entity : public Box<double>
{
    public:
        Entity(std::string type, PTexture texture);
        virtual ~Entity();

        virtual Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point<int> level_size, std::vector<std::shared_ptr<Humanoid>> humanoids) = 0;

        virtual void Render(SDL_Rect &camera);

    protected:

        Point<double> m_vel;

        double m_angle;

        Tile* TouchesWall(std::vector<std::shared_ptr<Tile>> tiles);

        std::string m_type;

    private:
        PTexture m_texture;
};

#endif // ENTITY_H
