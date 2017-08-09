#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include "wSDL.h"
#include "Player.h"
#include "ItemFrame.h"
#include "LTexture.h"
#include "LFont.h"

class Map
{
    public:
        Map(std::string file_path);
        virtual ~Map();

        //Returns true if game should quit
        bool HandleEvent(SDL_Event &e);

        void Update(double time_step = 1);
        void SetCamera();

        void Render();

        bool SetTiles();

        Point GetMapSizePixels();
        Point GetMapSizeTiles();

        void UpdateFPS(double fps);

        /*
            0 is the top left corner of the spritesheet, across, then down
        */
        static const int TILE_RED = 0;
        static const int TILE_TOP_LEFT = 1;
        static const int TILE_TOP = 2;
        static const int TILE_TOP_RIGHT = 3;
        static const int TILE_GREEN = 4;
        static const int TILE_LEFT = 5;
        static const int TILE_CENTER = 6;
        static const int TILE_RIGHT = 7;
        static const int TILE_BLUE = 8;
        static const int TILE_BOTTOM_LEFT = 9;
        static const int TILE_BOTTOM = 10;
        static const int TILE_BOTTOM_RIGHT = 11;

        static const int TILE_SPRITE_ROWS = 3;
        static const int TILE_SPRITE_COLS = 4;
        static const int TILE_TOTAL_SPRITES = TILE_SPRITE_ROWS * TILE_SPRITE_COLS;

        Point GetTileSize();

    private:
        std::string m_path_map;
        std::vector<std::shared_ptr<Tile>> m_tiles;

        std::shared_ptr<Player> m_player;
        SDL_Rect m_camera;

        Point m_tile_size;
        Point m_tile_grid;

        std::vector<std::shared_ptr<ItemFrame>> m_frames;

        static const int ITEM_FRAME_SIZE = 100;
        static const int ITEM_FRAME_SPACING = 10;
        static const int NUM_ITEM_FRAMES = 4;

        PTexture m_texture_tiles;

        int m_width, m_height;

        std::shared_ptr<LFont> m_font_fps;
        static const int FPS_X = 10;
        static const int FPS_Y = 10;

        void AddBorder();
        void AddItemFrames();
};

#endif // MAP_H
