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

class LSound;

using Point = SDL_Point;

struct DPoint
{
    double x = 0.f;
    double y = 0.f;
    DPoint() {};
    DPoint(double x, double y) : x(x), y(y) {};

    double dist()
    {
        return SDL_sqrt(SDL_pow(x, 2) + SDL_pow(y, 2));
    }
};

struct DRect
{
    double x = 0;
    double y = 0;
    double w = 0;
    double h = 0;
    DRect() : x(0), y(0), w(0), h(0) {};
    DRect(double x, double y, double w, double h) : x(x), y(y), w(w), h(h) {};
};


struct SDL_DelWindow {void operator()(SDL_Window*w) const {SDL_DestroyWindow(w);}};
std::unique_ptr<SDL_Window, SDL_DelWindow> sdl_unique_window(SDL_Window *w);


struct SDL_DelMixChunk {void operator()(Mix_Chunk *c) const {Mix_FreeChunk(c);}};
using unique_mix_chunk = std::unique_ptr<Mix_Chunk, SDL_DelMixChunk>;
unique_mix_chunk sdl_unique_mix_chunk(Mix_Chunk *c);

class wSDL
{
    public:
        static bool debug;
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;

        //What file types does this project use?
        static const int IMG_FLAGS = IMG_INIT_PNG;

        static std::shared_ptr<SDL_Window> s_window;
        static std::shared_ptr<SDL_Renderer> s_renderer;
        static std::shared_ptr<SDL_Surface> s_screen_surface;
        static std::shared_ptr<TTF_Font> s_font_skip_leg_day_20;

        static std::shared_ptr<LSound> s_bullet_fire;
        static std::shared_ptr<LSound> s_bullet_wall;

        static constexpr double PI =3.14159265f;

        static bool Init();
        static bool LoadMedia();
        static void Close();

        static bool CheckCollision(const DRect &a, const DRect &b);
        static bool CheckCollision(const DRect &a, const SDL_Rect &b);
        static bool CheckCollision(const SDL_Rect &a, const SDL_Rect &b);

        static DPoint Distance(const DRect &a, const DRect &b);
        static DPoint Distance(const DRect &a, const SDL_Rect &b);

        static DRect SDL_RectToDRect(const SDL_Rect &r);
        static DPoint SDL_PointToDPoint(const SDL_Point &p);


        static double GetAngle(const DPoint &a, const DPoint &b);
        static double GetAngle(const DPoint &a, const SDL_Point &b);

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


#endif // WSDL_H
