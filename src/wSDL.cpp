#include "wSDL.h"
#include "Player.h"
#include "Tile.h"
#include "Map.h"

SDL_Window *wSDL::s_window;
SDL_Renderer *wSDL::s_renderer;
SDL_Surface *wSDL::s_screen_surface;
TTF_Font *wSDL::s_font_skip_leg_day_20;

bool wSDL::Init()
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Warning: Linear texture filtering not enabled!");
    }

    s_window = SDL_CreateWindow("Cpp-ProjectV2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                wSDL::SCREEN_WIDTH, wSDL::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (s_window == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    s_renderer = SDL_CreateRenderer(s_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (s_renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(s_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if (!(IMG_Init(wSDL::IMG_FLAGS) & wSDL::IMG_FLAGS))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    else
    {
        wSDL::s_screen_surface = SDL_GetWindowSurface(wSDL::s_window);
    }

    if (TTF_Init() < 0)
    {
        printf("SDL_ttf could not initialize! SDL_ttf error: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

bool wSDL::LoadMedia(Map &m)
{
    bool success = Player::S_SetTexture() && Tile::S_SetTexture() && m.SetTiles();

    wSDL::s_font_skip_leg_day_20 = TTF_OpenFont("resources/fonts/SkipLegDay.ttf", 20);
    if (wSDL::s_font_skip_leg_day_20 == nullptr)
    {
        printf("Could not load 'Skip Leg Day' font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    return success;
}

void wSDL::Close(Map &m)
{
    m.Free();
    Player::S_Free();
    Tile::S_Free();

    SDL_DestroyRenderer(wSDL::s_renderer);
    SDL_DestroyWindow(wSDL::s_window);
    wSDL::s_renderer = nullptr;
    wSDL::s_window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

bool wSDL::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    int left_a = a.x, left_b = b.x;
    int right_a = a.x + a.w, right_b = b.x + b.w;
    int top_a = a.y, top_b = b.y;
    int bot_a = a.y + a.h, bot_b = b.y + b.h;

    if (bot_a <= top_b)
        return false;
    if (top_a >= bot_b)
        return false;
    if (right_a <= left_b)
        return false;
    if (left_a >= right_b)
        return false;

    return true;
}

void wSDL::ClearScreen()
{
    SDL_SetRenderDrawColor(wSDL::s_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(wSDL::s_renderer);
}

void wSDL::UpdateScreen()
{
    /*
    SDL_SetRenderDrawColor(wSDL::s_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine(wSDL::s_renderer, 0, wSDL::SCREEN_HEIGHT / 2, wSDL::SCREEN_WIDTH, wSDL::SCREEN_HEIGHT / 2);
    SDL_RenderDrawLine(wSDL::s_renderer, wSDL::SCREEN_WIDTH / 2, 0, wSDL::SCREEN_WIDTH / 2, wSDL::SCREEN_HEIGHT);
     */
    SDL_RenderPresent(wSDL::s_renderer);
}
