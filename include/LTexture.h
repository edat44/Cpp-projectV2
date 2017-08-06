#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "wSDL.h"
#include <string>
#include <memory>


class LTexture
{
    public:
        LTexture(std::string path, SDL_Color background = SDL_Color{0xFF, 0xFF, 0xFF, 0xFF});

        virtual ~LTexture();

        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue);
        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        virtual void SetBlendMode(SDL_BlendMode blending);

        virtual void SetAlpha(uint8_t alpha);

        virtual void Render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        int GetWidth();
        int GetHeight();
    private:
        std::shared_ptr<SDL_Texture> m_texture;
        std::string m_path;
        SDL_Color m_background;

        int m_width;
        int m_height;

        bool Load();
};

#endif // LTEXTURE_H
