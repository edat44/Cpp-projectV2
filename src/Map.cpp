#include "Map.h"


Map::Map(std::string file_path)
{
    this->m_file_path = file_path;
    this->m_camera = {0, 0, wSDL::SCREEN_WIDTH, wSDL::SCREEN_HEIGHT};
    this->m_player = new Player();
}

Map::~Map()
{
    this->Free();
}

bool Map::HandleEvent(SDL_Event &e)
{
    if ((e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) && e.key.repeat == 0)
    {
        if (e.key.keysym.sym == SDLK_ESCAPE)
            return true;
    }
    this->m_player->HandleEvent(e);
    return false;
}

void Map::MovePlayer()
{
    this->m_player->Move(this->m_tiles, this->GetPixelSize());
}

void Map::SetCamera()
{
    this->m_player->SetCamera(this->m_camera, this->GetPixelSize());
}

void Map::Render()
{
    for (std::vector<Tile*>::size_type i = 0; i < this->m_tiles.size(); ++i)
    {
        Tile* tile = this->m_tiles.at(i);
        tile->Render(this->m_camera);
    }
    this->m_player->Render(this->m_camera);
}

bool Map::SetTiles()
{
	//Success flag
	bool tiles_loaded = true;

    //The tile offsets
    int x = 0, y = Tile::S_HEIGHT;

    //Open the map
    std::ifstream map_file(this->m_file_path.c_str());

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
            x = Tile::S_WIDTH;
            std::istringstream iss(row_data);
            int tile_type = -1;

            while (iss >> tile_type)
            {
                //If the number is a valid tile number
                if(tile_type >= 0 && tile_type < Tile::TOTAL_TILE_SPRITES)
                {
                    this->m_tiles.push_back(new Tile(x, y, tile_type));
                }
                //If we don't recognize the tile type
                else
                {
                    //Stop loading map
                    printf("Error loading map: Invalid tile type (%d)!\n", tile_type);
                    tiles_loaded = false;
                    break;
                }
                x += Tile::S_WIDTH;
            }
            if (tiles_loaded == false)
                break;

            this->m_width = x;
			y += Tile::S_HEIGHT;
		}
		this->m_height = y;

		Point p;
		p.x = 1;
		p.y = 1;
		this->m_player->Position(p);
		this->AddBorder();
	}

    //Close the file
    map_file.close();

    //If the map was loaded fine
    return tiles_loaded;
}

void Map::Free()
{
    for (Tile* tile : this->m_tiles)
    {
        if (tile != nullptr)
        {
            delete tile;
            tile = nullptr;
        }
    }
}

Point Map::GetPixelSize()
{
    Point p;
    p.x = this->m_width;
    p.y = this->m_height;
    return p;
}

Point Map::GetTileSize()
{
    Point p;
    p.x = this->m_width / Tile::S_WIDTH;
    p.y = this->m_height / Tile::S_HEIGHT;
    return p;
}

void Map::AddBorder()
{
    Point s = Map::GetTileSize();
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
            tile_type = Tile::CENTER;
            x_add = 1;
            y_add = 0;
        }
        else if (i > top_left && i < top_right)
            tile_type = Tile::BOTTOM;
        else if (i == top_right)
        {
            tile_type = Tile::CENTER;
            x_add = 0;
            y_add = 1;
        }
        else if (i > top_right && i < bottom_right)
            tile_type = Tile::LEFT;
        else if (i == bottom_right)
        {
            tile_type = Tile::CENTER;
            x_add = -1;
            y_add = 0;
        }
        else if (i > bottom_right && i < bottom_left)
            tile_type = Tile::TOP;
        else if (i == bottom_left)
        {
            tile_type = Tile::CENTER;
            x_add = 0;
            y_add = -1;
        }
        else
            tile_type = Tile::RIGHT;

        this->m_tiles.push_back(new Tile(x, y, tile_type));

        x += (x_add * Tile::S_WIDTH);
        y += (y_add * Tile::S_HEIGHT);
    }
}
