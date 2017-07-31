#ifndef WSDL_H
#define WSDL_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class wSDL
{
    public:
        static const int SCREEN_WIDTH = 640;
        static const int SCREEN_HEIGHT = 480;

        //What file types does this project use?
        static const int IMG_FLAGS = IMG_INIT_PNG;

        static SDL_Window* s_window;
        static SDL_Renderer* s_renderer;


        static bool init();
        static bool loadMedia();
        static bool close();
};

#endif // WSDL_H
