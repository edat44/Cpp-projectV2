#ifndef WSDL_H
#define WSDL_H

#if defined(_WIN32) || defined(_WIN64)
    #include <SDL.h>
    #include <SDL_image.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
#endif
#include <stdio.h>

class Map;

using Point = SDL_Point;

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


        static bool Init();
        static bool LoadMedia(Map &m);
        static void Close(Map &m);

        static bool CheckCollision(SDL_Rect a, SDL_Rect b);

        static void ClearScreen();
        static void UpdateScreen();
};

#endif // WSDL_H
