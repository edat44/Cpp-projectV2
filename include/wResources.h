#ifndef WRESOURCES_H
#define WRESOURCES_H

#if defined(_WIN32) || defined(_WIN64)
    #include <SDL_ttf.h>
#else
    #include <SDL2_ttf/SDL_ttf.h>
#endif

#include <memory>

class LSound;
class LTexture;
class LSprite;

using PSound = std::shared_ptr<LSound>;
using PTexture = std::shared_ptr<LTexture>;
using PSprite = std::shared_ptr<LSprite>;

enum class SPRITE_MODE : uint8_t
{
    FORWARD =   0b00000001,
    BACKWARD =  0b00000010,
    BOUNCE =    0b00000100,
    STATIC =    0b00010000,
    DELETE =    0b00001000
};

class wResources
{
public:
    static std::string font_skip_leg_day;

    static PSound sound_bullet_fire;
    static PSound sound_bullet_wall;
    static PSound sound_arrow_swoosh;

    static PTexture texture_bullet;
    static PTexture texture_player;
    static PTexture texture_tiles;
    static PTexture texture_explosion;

    static bool Load();
};

#endif // WRESOURCES_H
