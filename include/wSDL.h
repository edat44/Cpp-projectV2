#ifndef WSDL_H
#define WSDL_H

#if defined(_WIN32) || defined(_WIN64)
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
    #include <SDL2_mixer/SDL_mixer.h>
#endif
#include <stdio.h>
#include <memory>
#include <string>
#include <cmath>
#include "wResources.h"
#include "Box.h"


struct SDL_DelTexture {void operator()(SDL_Texture *t) const {SDL_DestroyTexture(t);}};
using sdl_unique_texture = std::unique_ptr<SDL_Texture, SDL_DelTexture>;
sdl_unique_texture make_unique_texture(SDL_Texture *t);


struct SDL_DelMixChunk {void operator()(Mix_Chunk *c) const {Mix_FreeChunk(c);}};
using sdl_unique_mix_chunk = std::unique_ptr<Mix_Chunk, SDL_DelMixChunk>;
sdl_unique_mix_chunk make_unique_mix_chunk(Mix_Chunk *c);

struct SDL_DelFont {void operator()(TTF_Font *f) const {TTF_CloseFont(f);}};
using sdl_unique_font = std::unique_ptr<TTF_Font, SDL_DelFont>;
sdl_unique_font make_unique_font(TTF_Font *f);

class wSDL
{
public:
    static bool debug;
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

    static std::shared_ptr<SDL_Window> s_window;
    static std::shared_ptr<SDL_Renderer> s_renderer;
    static std::shared_ptr<SDL_Surface> s_screen_surface;

    //What file types does this project use?
    static const int IMG_FLAGS = IMG_INIT_PNG;

    static constexpr double PI =3.14159265f;

    //static constexpr SDL_Color COLOR_WHITE = SDL_Color{0xFF, 0xFF, 0xFF, 0xFF};
    //static constexpr SDL_Color COLOR_BLACK = SDL_Color{0x00, 0x00, 0x00, 0x00};

    static bool Init();
    static bool LoadMedia();
    static void Close();

    static bool CheckCollision(const Rect<double> &a, const Rect<double> &b);

    template <typename T1, typename T2>
    static bool CheckCollision(const Rect<T1> &a, const Rect<T2> &b);

    template <typename T>
    static bool CheckCollision(const Rect<T> &a, const SDL_Rect &b);

    static Rect<int> SDL_RectToIntRect(const SDL_Rect &r);

    template <typename T>
    static Point<T> Distance(const Rect<T> &a, const Rect<T> &b);

    static Point<double> Distance(const Rect<double> &a, const Rect<int> &b);

    static double GetAngle(const Point<double> &a, const Point<double> &b);

    template <typename T1, typename T2>
    static double GetAngle(const Point<T1> &a, const Point<T2> &b);

    static double Constrain(double val, double min_val, double max_val);

    static void ClearScreen();
    static void UpdateScreen();

    static void SDL_DelRes(SDL_Window   *r);
    static void SDL_DelRes(SDL_Renderer *r);
    static void SDL_DelRes(SDL_Texture  *r);
    static void SDL_DelRes(SDL_Surface  *r);
    static void SDL_DelRes(TTF_Font     *r);
    static void SDL_DelRes(Mix_Chunk    *r);
};

template <typename T>
std::shared_ptr<T> sdl_shared(T *t)
{
    return std::shared_ptr<T>(t, [](T *t) {wSDL::SDL_DelRes(t);});
}

template <typename T1, typename T2>
bool wSDL::CheckCollision(const Rect<T1> &a, const Rect<T2> &b)
{
    return wSDL::CheckCollision(a.ToDouble(), b.ToDouble());
}

template <typename T>
bool wSDL::CheckCollision(const Rect<T> &a, const SDL_Rect &b)
{
    Rect<int> b_int = wSDL::SDL_RectToIntRect(b);
    return wSDL::CheckCollision(a, b_int);
}


template <typename T>
Point<T> wSDL::Distance(const Rect<T> &a, const Rect<T> &b)
{
    double left_a = a.x, left_b = b.x;
    double right_a = a.x + a.w, right_b = b.x + b.w;
    double top_a = a.y, top_b = b.y;
    double bot_a = a.y + a.h, bot_b = b.y + b.h;

    Point<double> d;

    if (bot_a <= top_b)
        d.y = top_b - bot_a;
    if (top_a >= bot_b)
        d.y = bot_b - top_a;
    if (right_a <= left_b)
        d.x = left_b - right_a;
    if (left_a >= right_b)
        d.x = right_b - left_a;

    return d;
}

template <typename T1, typename T2>
double wSDL::GetAngle(const Point<T1> &a, const Point<T2> &b)
{
    return wSDL::GetAngle(a.ToDouble(), b.ToDouble());
}


#endif // WSDL_H
