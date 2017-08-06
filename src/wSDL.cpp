#include "wSDL.h"
#include "LSound.h"
#include <cmath>

bool wSDL::debug = false;
//int wSDL::SCREEN_WIDTH = 0;
//int wSDL::SCREEN_HEIGHT = 0;

std::shared_ptr<SDL_Window> wSDL::s_window;
std::shared_ptr<SDL_Renderer> wSDL::s_renderer;
std::shared_ptr<SDL_Surface> wSDL::s_screen_surface;
std::shared_ptr<TTF_Font> wSDL::s_font_skip_leg_day_20;
std::shared_ptr<LSound> wSDL::s_bullet_fire;
std::shared_ptr<LSound> wSDL::s_bullet_wall;

std::unique_ptr<SDL_Window, SDL_DelWindow> sdl_unique_window(SDL_Window *w) {return std::unique_ptr<SDL_Window, SDL_DelWindow>(w);}

unique_mix_chunk sdl_unique_mix_chunk(Mix_Chunk *c) {return unique_mix_chunk(c);}

bool wSDL::Init()
{
    // This line is only needed, if you want debug the program
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        printf("Warning: Linear texture filtering not enabled!");
    }

    s_window = sdl_shared(SDL_CreateWindow("Cpp-ProjectV2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                wSDL::SCREEN_WIDTH, wSDL::SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
    if (s_window == nullptr)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    //SDL_SetWindowFullscreen(s_window.get(), SDL_WINDOW_FULLSCREEN);

    s_renderer = sdl_shared(SDL_CreateRenderer(s_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (s_renderer == nullptr)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(s_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

    if (!(IMG_Init(wSDL::IMG_FLAGS) & wSDL::IMG_FLAGS))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    else
    {
        wSDL::s_screen_surface = sdl_shared(SDL_GetWindowSurface(wSDL::s_window.get()));
    }

    if (TTF_Init() < 0)
    {
        printf("SDL_ttf could not initialize! SDL_ttf error: %s\n", TTF_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

bool wSDL::LoadMedia()
{
    bool success = true;

    wSDL::s_font_skip_leg_day_20 = sdl_shared(TTF_OpenFont("resources/fonts/SkipLegDay.ttf", 20));
    if (wSDL::s_font_skip_leg_day_20 == nullptr)
    {
        printf("Could not load 'Skip Leg Day' font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    wSDL::s_bullet_fire = std::make_shared<LSound>("resources/gun_shot.wav");
    if (wSDL::s_bullet_fire == nullptr)
    {
        printf("Could not load gun_shot.wav! %s\n", Mix_GetError());
        success = false;
    }

    wSDL::s_bullet_wall = std::make_shared<LSound>("resources/explosion_mini.wav");
    if (wSDL::s_bullet_wall == nullptr)
    {
        printf("Could not load explosion_mini.wav.wav! %s\n", Mix_GetError());
        success = false;
    }

    return success;
}

void wSDL::Close()
{
    /*
    SDL_DestroyRenderer(wSDL::s_renderer.get());
    SDL_DestroyWindow(wSDL::s_window.get());
    */

    IMG_Quit();
    SDL_Quit();
    Mix_Quit();
}

bool wSDL::CheckCollision(const DRect &a, const DRect &b)
{
    double left_a = a.x, left_b = b.x;
    double right_a = a.x + a.w, right_b = b.x + b.w;
    double top_a = a.y, top_b = b.y;
    double bot_a = a.y + a.h, bot_b = b.y + b.h;

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

bool wSDL::CheckCollision(const DRect &a, const SDL_Rect &b)
{
    return wSDL::CheckCollision(a, wSDL::SDL_RectToDRect(b));
}

bool wSDL::CheckCollision(const SDL_Rect &a, const SDL_Rect &b)
{
    return wSDL::CheckCollision(SDL_RectToDRect(a), SDL_RectToDRect(b));
}

DRect wSDL::SDL_RectToDRect(const SDL_Rect &r)
{
    return DRect{(double)r.x, (double)r.y, (double)r.w, (double)r.h};
}

DPoint wSDL::SDL_PointToDPoint(const SDL_Point &p)
{
    return DPoint{(double)p.x, (double)p.y};
}


DPoint wSDL::Distance(const DRect &a, const DRect &b)
{
    double left_a = a.x, left_b = b.x;
    double right_a = a.x + a.w, right_b = b.x + b.w;
    double top_a = a.y, top_b = b.y;
    double bot_a = a.y + a.h, bot_b = b.y + b.h;

    DPoint d;

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

DPoint wSDL::Distance(const DRect &a, const SDL_Rect &b)
{
    return Distance(a, wSDL::SDL_RectToDRect(b));
}

double wSDL::GetAngle(const DPoint &a, const DPoint &b)
{
    double angle = 0.0;
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    if (dx == 0.0)
        angle = 90.0;
    else
        angle = atan(fabs(dy) / fabs(dx)) * 180.0 / PI;

    if (b.x <= a.x && b.y >= a.y)         //Q4 (topright)
        angle = 180.0 - angle;
    else if (b.x < a.x && b.y < a.y)      //Q1 (bottomright)
        angle += 180.0;
    else if (b.x >= a.x && b.y <= a.y)    //Q2 (bottomleft)
        angle = -angle;
    else                                  //Q3 (topleft)
        angle = angle;
    return angle;
}

double wSDL::GetAngle(const DPoint &a, const SDL_Point &b)
{
    return wSDL::GetAngle(a, wSDL::SDL_PointToDPoint(b));
}

double wSDL::Constrain(double val, double min_val, double max_val)
{
    return std::min(std::max(val, min_val), max_val);
}

void wSDL::ClearScreen()
{
    SDL_SetRenderDrawColor(wSDL::s_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(wSDL::s_renderer.get());
}

void wSDL::UpdateScreen()
{
    SDL_RenderPresent(wSDL::s_renderer.get());
}

void wSDL::SDL_DelRes(SDL_Window   *r) {SDL_DestroyWindow(r);}
void wSDL::SDL_DelRes(SDL_Renderer *r) {SDL_DestroyRenderer(r);}
void wSDL::SDL_DelRes(SDL_Texture  *r) {SDL_DestroyTexture(r);}
void wSDL::SDL_DelRes(SDL_Surface  *r) {SDL_FreeSurface(r);}
void wSDL::SDL_DelRes(TTF_Font     *r) {TTF_CloseFont(r);}
void wSDL::SDL_DelRes(Mix_Chunk    *r) {Mix_FreeChunk(r);}
