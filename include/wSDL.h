#ifndef WSDL_H
#define WSDL_H

#if defined(_WIN32) || defined(_WIN64)
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
#endif
#include <stdio.h>

class Map;

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

class wSDL
{
    public:
        static const int SCREEN_WIDTH = 640;
        static const int SCREEN_HEIGHT = 480;

        //What file types does this project use?
        static const int IMG_FLAGS = IMG_INIT_PNG;

        static SDL_Window* s_window;
        static SDL_Renderer* s_renderer;
        static SDL_Surface* s_screen_surface;
        static TTF_Font* s_font_skip_leg_day_20;


        static bool Init();
        static bool LoadMedia(Map &m);
        static void Close(Map &m);

        static bool CheckCollision(const DRect &a, const DRect &b);
        static bool CheckCollision(const DRect &a, const SDL_Rect &b);
        static bool CheckCollision(const SDL_Rect &a, const SDL_Rect &b);

        static DPoint Distance(const DRect &a, const DRect &b);
        static DPoint Distance(const DRect &a, const SDL_Rect &b);

        static DRect SDL_RectToDRect(const SDL_Rect &r);

        static void ClearScreen();
        static void UpdateScreen();
};

#endif // WSDL_H
