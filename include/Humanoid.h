#ifndef HUMANOID_H
#define HUMANOID_H

#include <Entity.h>
#include <string>

class Humanoid : public Entity
{
    public:
        Humanoid(std::string type, std::string path_texture);
        virtual ~Humanoid();

        virtual Tile* Move(double time_step, std::vector<Tile*> tiles, Point level_size) = 0;
        virtual void Free() = 0;

    protected:

    private:
};

#endif // HUMANOID_H
