#include "Map.h"

const std::string Map::m_path_texture_tiles = "resources/tiles.png";

Map::Map(std::string file_path)
{
    this->m_path_map = file_path;
    this->m_camera = {0, 0, wSDL::SCREEN_WIDTH, wSDL::SCREEN_HEIGHT};
    this->m_player = std::make_shared<Player>();

    this->LoadTextures();
    this->AddItemFrames();
    this->SetTiles();
}

Map::~Map()
{
    this->m_tiles.erase(this->m_tiles.begin(), this->m_tiles.end());
    this->m_frames.erase(this->m_frames.begin(), this->m_frames.end());
}

bool Map::HandleEvent(SDL_Event &e)
{
    if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.repeat == 0)
    {
        if (e.key.keysym.sym == SDLK_ESCAPE)
            return true;
    }
    this->m_player->HandleEvent(e, this->m_camera);
    return false;
}

void Map::MovePlayer(double time_step)
{
    this->m_player->Move(time_step, this->m_tiles, this->GetMapSizePixels());
}

void Map::SetCamera()
{
    this->m_player->SetCamera(this->m_camera, this->GetMapSizePixels());
}

void Map::Render()
{
    for (std::shared_ptr<Tile> tile : this->m_tiles)
    {
        tile->Render(this->m_camera);
    }
    this->m_player->Render(this->m_camera);
    for (std::shared_ptr<ItemFrame> frame : this->m_frames)
    {
        frame->Render();
    }
    if (this->m_font_fps != nullptr)
        this->m_font_fps->Render(Map::FPS_X, Map::FPS_Y);
}

bool Map::SetTiles()
{
	//Success flag
	bool tiles_loaded = true;

    //The tile offsets
    int x = 0, y = Map::TILE_HEIGHT;

    //Open the map
    std::ifstream map_file(this->m_path_map.c_str());

    //If the map couldn't be loaded
    if(map_file.fail())
    {
		printf( "Unable to load map file!\n" );
		tiles_loaded = false;
    }
	else
	{
	    std::string row_data;
		//Initialize the tiles
        while (std::getline(map_file, row_data))
        {
            x = Map::TILE_WIDTH;
            std::istringstream iss(row_data);
            int tile_type = -1;

            while (iss >> tile_type)
            {
                //If the number is a valid tile number
                if(tile_type >= 0 && tile_type < Map::TILE_TOTAL_SPRITES)
                {
                    this->m_tiles.push_back(std::make_shared<Tile>(x, y, tile_type, this->m_texture_tiles, &this->m_tile_clips));
                }
                //If we don't recognize the tile type
                else
                {
                    //Stop loading map
                    printf("Error loading map: Invalid tile type (%d)!\n", tile_type);
                    tiles_loaded = false;
                    break;
                }
                x += Map::TILE_WIDTH;
            }
            if (tiles_loaded == false)
                break;

            this->m_width = x;
			y += Map::TILE_HEIGHT;
		}
		this->m_height = y;

		DPoint p;
		p.x = 1.f;
		p.y = 1.f;
		this->m_player->Position(p);
		this->AddBorder();
	}

    //Close the file
    map_file.close();

    //If the map was loaded fine
    return tiles_loaded;
}

bool Map::LoadTextures()
{
    bool success = true;
    this->m_texture_tiles = std::make_shared<LTexture>();
    if (!this->m_texture_tiles->LoadFromFile(this->m_path_texture_tiles))
    {
        printf("Failed to load tile texture\n");
        success = false;
    }
    for (int y = 0; y < Map::TILE_SPRITE_ROWS; ++y)
    {
        for (int x = 0; x < Map::TILE_SPRITE_COLS; ++x)
        {
            this->m_tile_clips.push_back({x * Map::TILE_WIDTH, y * Map::TILE_HEIGHT, Map::TILE_WIDTH, Map::TILE_HEIGHT});
        }
    }
    this->m_font_fps = std::make_shared<LFont>(wResources::font_skip_leg_day, 20, SDL_Color{0xCC, 0xCC, 0xCC, 0xFF});
    return success;
}

Point Map::GetMapSizePixels()
{
    Point p;
    p.x = this->m_width;
    p.y = this->m_height;
    return p;
}

Point Map::GetMapSizeTiles()
{
    Point p;
    p.x = this->m_width / Map::TILE_WIDTH;
    p.y = this->m_height / Map::TILE_HEIGHT;
    return p;
}

void Map::UpdateFPS(double fps)
{
    std::stringstream time_text;
    time_text.str("");
    time_text << "FPS: " << fps;
    if (this->m_font_fps != nullptr)
        this->m_font_fps->ChangeText(time_text.str());
}

void Map::AddBorder()
{
    Point s = Map::GetMapSizeTiles();
    int border_tiles = (s.y * 2) + (s.x * 2) - 4;
    int x = 0, y = 0;

    int x_add = 1, y_add = 0;

    //Start at top left and work way clockwise
    for (int i = 0; i < border_tiles; ++i)
    {
        int top_left = 0,
            top_right = s.x - 1,
            bottom_right = top_right + s.y - 1,
            bottom_left = bottom_right + s.x -1;

        int tile_type = -1;

        if (i == top_left)
        {
            tile_type = Map::TILE_CENTER;
            x_add = 1;
            y_add = 0;
        }
        else if (i > top_left && i < top_right)
            tile_type = Map::TILE_BOTTOM;
        else if (i == top_right)
        {
            tile_type = Map::TILE_CENTER;
            x_add = 0;
            y_add = 1;
        }
        else if (i > top_right && i < bottom_right)
            tile_type = Map::TILE_LEFT;
        else if (i == bottom_right)
        {
            tile_type = Map::TILE_CENTER;
            x_add = -1;
            y_add = 0;
        }
        else if (i > bottom_right && i < bottom_left)
            tile_type = Map::TILE_TOP;
        else if (i == bottom_left)
        {
            tile_type = Map::TILE_CENTER;
            x_add = 0;
            y_add = -1;
        }
        else
            tile_type = Map::TILE_RIGHT;

        this->m_tiles.push_back(std::make_shared<Tile>(x, y, tile_type, this->m_texture_tiles, &this->m_tile_clips));

        x += (x_add * Map::TILE_WIDTH);
        y += (y_add * Map::TILE_HEIGHT);
    }
}

void Map::AddItemFrames()
{
    int x = wSDL::SCREEN_WIDTH - Map::ITEM_FRAME_SIZE - Map::ITEM_FRAME_SPACING;
    int y = wSDL::SCREEN_HEIGHT - Map::ITEM_FRAME_SIZE - Map::ITEM_FRAME_SPACING;
    for (int i = 0; i < Map::NUM_ITEM_FRAMES; ++i)
    {
        int s = Map::ITEM_FRAME_SIZE;
        this->m_frames.push_back(std::make_shared<ItemFrame>(x, y, s));
        x -= (Map::ITEM_FRAME_SIZE + Map::ITEM_FRAME_SPACING);
    }
}
