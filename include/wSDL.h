#ifndef WSDL_H
#define WSDL_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Map;

struct Point
{
    int x = 0;
    int y = 0;
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


        static bool Init();
        static bool LoadMedia(Map &m);
        static void Close(Map &m);

        static bool CheckCollision(SDL_Rect a, SDL_Rect b);

        static void ClearScreen();
        static void UpdateScreen();
};

#endif // WSDL_H
