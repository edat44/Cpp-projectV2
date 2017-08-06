#include "wResources.h"

#include "wSDL.h"
#include "LSound.h"


std::string wResources::font_skip_leg_day = "resources/fonts/SkipLegDay.ttf";

std::shared_ptr<LSound> wResources::sound_bullet_fire;
std::shared_ptr<LSound> wResources::sound_bullet_wall;

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
        printf("Could not load explosion_mini.wav.wav! %s\n", Mix_GetError());
        success = false;
    }

    return success;
}
