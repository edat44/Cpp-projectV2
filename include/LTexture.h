#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "wSDL.h"
#include "LGraphic.h"
#include <string>


class LTexture : public LGraphic
{
    public:
        LTexture();
        virtual ~LTexture();

        bool LoadFromFile(std::string path);

        #ifdef _SDL_TTF_H
        bool LoadFromRenderedText(std::string texture_text, SDL_Color text_color);
        #endif

        virtual void Free();

        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue);
        virtual void SetColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        virtual void SetBlendMode(SDL_BlendMode blending);

        virtual void SetAlpha(uint8_t alpha);

        virtual void Render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

    protected:

    private:
        SDL_Texture* m_texture;
};

#endif // LTEXTURE_H
