#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <string>
#include <fstream>
#include <sstream>
#include "wSDL.h"
#include "Player.h"
#include "ItemFrame.h"

class Map
{
    public:
        Map(std::string file_path);
        virtual ~Map();

        //Returns true if game should quit
        bool HandleEvent(SDL_Event &e);

        void MovePlayer(double time_step = 1);
        void SetCamera();

        void Render();

        bool SetTiles();
        void Free();

        Point GetPixelSize();
        Point GetTileSize();

    private:
        std::string m_file_path;
        std::vector<Tile*> m_tiles;

        Player* m_player;
        SDL_Rect m_camera;

        int m_width, m_height;

        std::vector<ItemFrame*> m_frames;

        static const int ITEM_FRAME_SIZE = 100;
        static const int ITEM_FRAME_SPACING = 10;
        static const int NUM_ITEM_FRAMES = 0;

        void AddBorder();
        void AddItemFrames();
};

#endif // MAP_H
