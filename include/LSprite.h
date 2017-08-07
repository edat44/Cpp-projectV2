#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include "LTexture.h"
#include "wSDL.h"
#include "LTimer.h"

class LSprite : public LTexture
{
    public:
        LSprite(const LTexture &texture, int start_frame, int frame_time, SPRITE_MODE mode);
        virtual ~LSprite();

        virtual void Render(SDL_Rect &camera, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
        virtual void Render(SDL_Rect &camera, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void NextFrame();

        static const SPRITE_MODE SPRITE_FORWARD =           0b00000001;
        static const SPRITE_MODE SPRITE_BACKWARD =          0b00000010;
        static const SPRITE_MODE SPRITE_FORWARD_BACKWARD =  0b00000100;
        static const SPRITE_MODE SPRITE_BACKWARD_FORWARD =  0b00001000;
        static const SPRITE_MODE SPRITE_STATIC =            0b00010000;
        static const SPRITE_MODE SPRITE_DELETE =            0b00100000;
        static const SPRITE_MODE SPRITE_CONTINUOUS =        0b01000000;

    private:
        void SetClips();

        std::vector<SDL_Rect> m_clips;

        int m_current_frame;
        int m_frame_time;
        int m_frame_direction;
        SPRITE_MODE m_mode;
        std::unique_ptr<LTimer> m_frame_timer;
};

#endif // SPRITE_H
