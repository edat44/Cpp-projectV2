#ifndef HUMANOID_H
#define HUMANOID_H

#include <Entity.h>
#include <string>
#include <memory>

class Humanoid : public Entity
{
    public:
        Humanoid(std::string type, std::string path_texture);
        virtual ~Humanoid();

        virtual Tile* Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size) = 0;

    protected:

    private:
};

#endif // HUMANOID_H
