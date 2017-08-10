#include "Map.h"

Map::Map(std::string file_path)
{
    this->m_path_map = file_path;
    this->m_camera = {0, 0, wSDL::SCREEN_WIDTH, wSDL::SCREEN_HEIGHT};
    this->m_player = std::make_shared<Player>(this);
    
    m_humanoids.push_back(m_player);

    this->m_texture_tiles = wResources::texture_tiles;
    this->m_tile_size = m_texture_tiles->GetSize();

    this->m_font_fps = std::make_shared<LFont>(wResources::font_skip_leg_day, 20, SDL_Color{0xCC, 0xCC, 0xCC, 0xFF});

    this->AddItemFrames();
    this->SetTiles();
    
     m_humanoids.push_back(std::make_shared<Monster>(this));
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

void Map::Update(double time_step)
{
    for (auto& humanoid : m_humanoids)
    {
        humanoid->Move(time_step, this->m_tiles, this->GetMapSizePixels());
    }
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
    for (auto& humanoid : m_humanoids)
    {
        humanoid->Render(this->m_camera);
    }
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

	m_tile_grid.x = 0;
	m_tile_grid.y = 0;

    //The tile offsets
    int x = 0, y = 0;

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
            if (row_data.find("END") != std::string::npos)
                break;
            x = 0;
            std::istringstream iss(row_data);

            std::string tile_data;
            int tile_type = -1;

            //Read in the tile_data
            while (iss >> tile_data)
            {
                //If the number is a valid tile number
                //tile_type = std::atoi(tile_data.substr(0, tile_digit_length).c_str());
                std::istringstream iss2{tile_data};
                std::string tile_type_str;

                std::getline(iss2, tile_type_str, '*');
                tile_type = std::atoi(tile_type_str.c_str());

                std::string tile_meta_data_key;
                std::getline(iss2, tile_meta_data_key);
                if (wSDL::debug && !tile_meta_data_key.empty())
                    printf("Tile Meta Data Key: %s\n", tile_meta_data_key.c_str());


                if(tile_type >= 0 && tile_type < Map::TILE_TOTAL_SPRITES)
                {
                    this->m_tiles.push_back(std::make_shared<Tile>(x, y, tile_type, this->m_texture_tiles, tile_meta_data_key));
                }
                //If we don't recognize the tile type
                else
                {
                    //Stop loading map
                    printf("Error loading map: Invalid tile type (%d)!\n", tile_type);
                    tiles_loaded = false;
                    break;
                }
                x += m_tile_size.x;
                if (y == 0)
                    m_tile_grid.x++;

            }
            if (tiles_loaded == false)
                break;

            this->m_width = x;
			y += m_tile_size.y;
			m_tile_grid.y++;
		}
		this->m_height = y;

		DPoint p;
		p.x = 1.f;
		p.y = 1.f;
		this->m_player->SetPosition(p, m_tile_size);
		this->AddBorder();
	}

    //Close the file
    map_file.close();

    //If the map was loaded fine
    return tiles_loaded;
}

Point Map::GetMapSizePixels()
{
    Point p;
    p.x = m_tile_grid.x * m_tile_size.x;
    p.y = m_tile_grid.y * m_tile_size.y;
    return p;
}

Point Map::GetMapSizeTiles()
{
    return m_tile_grid;
}

Point Map::GetTileSize()
{
    return m_tile_size;
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
    for (auto& tile : m_tiles)
    {
        tile->Shift(1, 1);
    }

    Point s = m_tile_grid;
    int border_tiles = (s.y * 2) + (s.x * 2) + 4;
    int x = 0, y = 0;

    int x_add = 1, y_add = 0;

    int top_left = 0,
    top_right = s.x + 1,
    bottom_right = top_right + s.y + 1,
    bottom_left = bottom_right + s.x + 1;

    //Start at top left and work way clockwise
    for (int i = 0; i < border_tiles; ++i)
    {

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

        this->m_tiles.push_back(std::make_shared<Tile>(x, y, tile_type, this->m_texture_tiles));


        x += (x_add * m_tile_size.x);
        y += (y_add * m_tile_size.y);
    }
    m_tile_grid.x += 2;
    m_tile_grid.y += 2;
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
