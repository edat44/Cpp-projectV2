#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <string>
#include <fstream>
#include <sstream>

class Map
{
    public:
        Map(std::string file_path);
        virtual ~Map();

        bool SetTiles();
        void Free();

    private:
        std::string m_file_path;
        std::vector<Tile*> m_tiles;
};

#endif // MAP_H
