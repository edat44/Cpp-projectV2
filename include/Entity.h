#ifndef ENTITY_H
#define ENTITY_H

#include "Tile.h"
#include "LTexture.h"
#include <vector>
#include <string>
#include <memory>

class Entity
{
    public:
        Entity(std::string type, PTexture texture);
        virtual ~Entity();

        void Position(DPoint pos);

        virtual Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size) = 0;

        virtual void Render(SDL_Rect &camera);

    protected:
        DRect m_box;

        DPoint m_vel;

        double m_angle;

        Tile* TouchesWall(std::vector<std::shared_ptr<Tile>> tiles);

        std::string m_type;

    private:
        PTexture m_texture;
};

#endif // ENTITY_H
