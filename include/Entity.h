#ifndef ENTITY_H
#define ENTITY_H

#include "Tile.h"
#include "LTexture.h"
#include <vector>
#include <string>

class Entity
{
    public:
        Entity(std::string path_texture);
        virtual ~Entity();
    
    virtual void Move(double time_step, std::vector<Tile*> tiles, Point level_size);
    
    void Render(SDL_Rect &camera);
    
    virtual void Free();
    
    protected:
        DRect m_box;
    
        DPoint m_vel;
    
        double m_angle;
    
        Tile* TouchesWall(std::vector<Tile*> tiles);
    
    private:
        bool LoadTexture();
    
        std::string m_path_texture;
    
        LTexture *m_texture;
};

#endif // ENTITY_H
