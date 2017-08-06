#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include "LTexture.h"
#include "wSDL.h"

class LSprite : LTexture
{
    public:
        LSprite(const LTexture &texture, int start_frame = 0, int frame_time = 0, SPRITE_MODE mode = SPRITE_MODE::BOUNCE);
        virtual ~LSprite();

        virtual void Render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void NextFrame();
    private:
        void SetClips();

        std::vector<SDL_Rect> m_clips;

        int m_current_frame;
        int m_frame_time;
        SPRITE_MODE m_mode;
};

#endif // SPRITE_H
