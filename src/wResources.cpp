#include "wResources.h"

#include "wSDL.h"
#include "LSound.h"
#include "LTexture.h"


std::string wResources::font_skip_leg_day = "resources/fonts/SkipLegDay.ttf";

PSound wResources::sound_bullet_fire;
PSound wResources::sound_bullet_wall;
PSound wResources::sound_arrow_swoosh;

PTexture wResources::texture_bullet;
PTexture wResources::texture_player;
PTexture wResources::texture_tiles;
PTexture wResources::texture_explosion;

bool wResources::Load()
{
    bool success = true;

    //wResources::font_skip_leg_day_20 = sdl_shared(TTF_OpenFont("resources/fonts/SkipLegDay.ttf", 20));
    //if (wResources::font_skip_leg_day_20 == nullptr)
    //{
    //    printf("Could not load 'Skip Leg Day' font! SDL_ttf Error: %s\n", TTF_GetError());
    //    success = false;
    //}

    wResources::sound_bullet_fire = std::make_shared<LSound>("resources/gun_shot.wav");
    if (wResources::sound_bullet_fire == nullptr)
    {
        printf("Could not load gun_shot.wav! %s\n", Mix_GetError());
        success = false;
    }

    wResources::sound_bullet_wall = std::make_shared<LSound>("resources/explosion_mini.wav");
    if (wResources::sound_bullet_wall == nullptr)
    {
        printf("Could not load explosion_mini.wav! %s\n", Mix_GetError());
        success = false;
    }
    wResources::sound_arrow_swoosh = std::make_shared<LSound>("resources/arrow_swoosh.wav");
    if (wResources::sound_arrow_swoosh == nullptr)
    {
        printf("Could not load arrow_swoosh.wav! %s\n", Mix_GetError());
        success = false;
    }

    wResources::texture_bullet = std::make_shared<LTexture>("resources/bullet.png");
    if (wResources::texture_bullet == nullptr)
    {
        printf("Could not load bullet.png! %s\n", SDL_GetError());
    }

    wResources::texture_player = std::make_shared<LTexture>("resources/dot_with_arrow.png");
    if (wResources::texture_player == nullptr)
    {
        printf("Could not load dot_with_arrow.png! %s\n", SDL_GetError());
    }

    wResources::texture_tiles = std::make_shared<LTexture>("resources/tiles.png");
    if (wResources::texture_tiles == nullptr)
    {
        printf("Could not load tiles.png! %s\n", SDL_GetError());
    }

    wResources::texture_explosion = std::make_shared<LTexture>("resources/explosion_sprite.png");
    if (wResources::texture_explosion == nullptr)
    {
        printf("Could not load explosion_sprite.png! %s\n", SDL_GetError());
    }

    return success;
}
