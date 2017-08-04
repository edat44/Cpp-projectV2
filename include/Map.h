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
        bool LoadTexture();
        void Free();

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

        static const int TILE_WIDTH = 80;
        static const int TILE_HEIGHT = 80;

    private:
        std::string m_path_map;
        std::vector<Tile*> m_tiles;

        Player* m_player;
        SDL_Rect m_camera;

        int m_width, m_height;

        std::vector<ItemFrame*> m_frames;

        static const int ITEM_FRAME_SIZE = 100;
        static const int ITEM_FRAME_SPACING = 10;
        static const int NUM_ITEM_FRAMES = 0;

        LTexture *m_texture_tiles;
        static const std::string m_path_texture_tiles;
        std::vector<SDL_Rect> m_tile_clips;

        LTexture *m_texture_fps;
        static const int FPS_X = 10;
        static const int FPS_Y = 10;

        void AddBorder();
        void AddItemFrames();
};

#endif // MAP_H
