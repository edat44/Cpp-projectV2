#include "wResources.h"

#include "wSDL.h"
#include "LSound.h"
#include "LTexture.h"


std::string wResources::font_skip_leg_day = "resources/fonts/SkipLegDay.ttf";

PSound wResources::sound_bullet_fire;
PSound wResources::sound_explosion_mini;
PSound wResources::sound_arrow_swoosh;

PTexture wResources::texture_bullet;
PTexture wResources::texture_player;
PTexture wResources::texture_tiles;
PTexture wResources::texture_explosion;

bool wResources::Load()
{
    bool success = true;

    try
    {
        wResources::sound_bullet_fire = std::make_shared<LSound>("resources/gun_shot.wav");
        wResources::sound_explosion_mini = std::make_shared<LSound>("resources/explosion_mini.wav");
        wResources::sound_arrow_swoosh = std::make_shared<LSound>("resources/arrow_swoosh.wav");

        wResources::texture_bullet = std::make_shared<LTexture>("resources/bullet.png");
        wResources::texture_player = std::make_shared<LTexture>("resources/dot_with_arrow.png");
        wResources::texture_tiles = std::make_shared<LTexture>("resources/tiles.png", 3, 4);
        wResources::texture_explosion = std::make_shared<LTexture>("resources/explosion_sprite.png", 1, 10);
    }
    catch (std::exception &e)
    {
        printf("Failed to load media!\n");
        success = false;
    }

    return success;
}
