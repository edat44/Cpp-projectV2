#include "Monster.h"
#include "Map.h"

Monster::Monster(Map *map)
    : Humanoid("Monster", wResources::texture_doge, map)
{
    this->SetPosition(DPoint {11, 2}, map->GetTileSize());
}

Monster::~Monster()
{
    
}

void Monster::Render(SDL_Rect &camera)
{
    this->Humanoid::Render(camera);
}

Tile* Monster::Move(double time_step, std::vector<std::shared_ptr<Tile>> tiles, Point level_size)
{
    Tile* tile = this->Humanoid::Move(time_step, tiles, level_size);
    return tile;
}
