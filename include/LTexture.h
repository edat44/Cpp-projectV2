#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "wSDL.h"
#include <string>
#include <memory>
#include "Box.h"

using SPRITE_MODE = uint8_t;

class LTexture : public Box<int>
{
    public:
        LTexture(std::string path, int clip_rows = 1, int clip_cols = 1, SDL_Color background_mask = SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});
        virtual ~LTexture();

        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue);
        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        virtual void SetBlendMode(SDL_BlendMode blending);

        virtual void SetAlpha(uint8_t alpha);

        virtual void Render(SDL_Rect &camera, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
        virtual void Render(SDL_Rect &camera, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        PSprite MakeSprite(int start_frame, int frame_time, SPRITE_MODE mode);

    protected:
        LTexture(const LTexture &texture);
        LTexture();

        std::string m_path;
        std::shared_ptr<SDL_Texture> m_texture;

        Point<int> m_original_size;

        int m_clip_rows;
        int m_clip_cols;

        SDL_Color m_background_mask;

    private:
        void Load();
};

#endif // LTEXTURE_H
