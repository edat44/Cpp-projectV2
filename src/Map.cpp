#include "Map.h"


Map::Map(std::string file_path)
{
    this->m_file_path = file_path;
}

Map::~Map()
{
    //dtor
}

bool Map::SetTiles()
{
	//Success flag
	bool tiles_loaded = true;

    //The tile offsets
    int x = 0, y = 0;

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
            x = 0;
            std::istringstream iss(row_data);
            int tile_type = -1;

            while (iss >> tile_type)
            {
                //If the number is a valid tile number
                if(tile_type >= 0 && tile_type < Tile::TOTAL_TILE_SPRITES)
                {
                    m_tiles.push_back(new Tile(x, y, tile_type));
                }
                //If we don't recognize the tile type
                else
                {
                    //Stop loading map
                    printf( "Error loading map: Invalid tile type (%d)!\n", tile_type );
                    tiles_loaded = false;
                    break;
                }
                x += Tile::S_WIDTH;
            }
            if (tiles_loaded == false)
                break;

			y += Tile::S_HEIGHT;
		}
	}

    //Close the file
    map_file.close();

    //If the map was loaded fine
    return tiles_loaded;
}

void Map::Free()
{

}
