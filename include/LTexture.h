#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "wSDL.h"
#include <string>
#include <memory>

using SPRITE_MODE = uint8_t;

class LTexture
{
    public:
        LTexture(std::string path, int clip_rows = 1, int clip_cols = 1, SDL_Color background_mask = SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
        LTexture(const LTexture &texture);
        virtual ~LTexture();

        void SetPosition(const Point &pos);
        void SetPosition(int x, int y);

        void SetColor(uint8_t red, uint8_t green, uint8_t blue);
        void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        void SetBlendMode(SDL_BlendMode blending);

        void SetAlpha(uint8_t alpha);

        virtual void Render(SDL_Rect &camera, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
        virtual void Render(SDL_Rect &camera, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        Point GetPosition();
        int GetWidth();
        int GetHeight();

        PSprite MakeSprite(int start_frame, int frame_time, SPRITE_MODE mode);

    protected:
        LTexture(PTexture texture);

        std::string m_path;
        std::shared_ptr<SDL_Texture> m_texture;
        int m_width;
        int m_height;

        int m_clip_rows;
        int m_clip_cols;

        Point m_pos;

        SDL_Color m_background_mask;
    private:

        bool Load();
};

#endif // LTEXTURE_H
