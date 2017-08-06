#ifndef WRESOURCES_H
#define WRESOURCES_H

#if defined(_WIN32) || defined(_WIN64)
    #include <SDL_ttf.h>
#else
    #include <SDL2_ttf/SDL_ttf.h>
#endif

#include <memory>

class LSound;

class wResources
{
public:
    static std::string font_skip_leg_day;

    static std::shared_ptr<LSound> sound_bullet_fire;
    static std::shared_ptr<LSound> sound_bullet_wall;

    static bool Load();
};

#endif // WRESOURCES_H
