#ifndef ENTITY_H
#define ENTITY_H

#include "Tile.h"
#include "LTexture.h"
#include <vector>
#include <string>

class Entity
{
    public:
        Entity(std::string type, std::string path_texture);
        virtual ~Entity();

        void Position(DPoint pos);

        virtual Tile* Move(double time_step, std::vector<Tile*> tiles, Point level_size) = 0;

        virtual void Render(SDL_Rect &camera);

        virtual void Free() = 0;

    protected:
        DRect m_box;

        DPoint m_vel;

        double m_angle;

        Tile* TouchesWall(std::vector<Tile*> tiles);

        std::string m_type;

    private:
        bool LoadTexture();

        std::string m_path_texture;

        LTexture *m_texture;
};

#endif // ENTITY_H
