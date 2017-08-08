#ifndef LFONT_H
#define LFONT_H

#include "wSDL.h"
#include <string>
#include <memory>

class LFont
{
    public:
        LFont(std::string font_path, int pt_size, SDL_Color color, std::string text = " ");
        virtual ~LFont();

        virtual void Render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void ChangeText(std::string text);

        int GetWidth();
        int GetHeight();

    private:
        std::shared_ptr<SDL_Texture> m_texture;

        int m_width;
        int m_height;

        std::string m_text;
        std::string m_font_path;
        int m_pt_size;
        std::shared_ptr<TTF_Font> m_font;
        SDL_Color m_color;

        void Load();
};

#endif // LFONT_H
