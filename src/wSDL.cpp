#include "wSDL.h"

bool wSDL::debug = true;
int wSDL::SCREEN_WIDTH = 900;
int wSDL::SCREEN_HEIGHT = 650;

std::shared_ptr<SDL_Window> wSDL::s_window;
std::shared_ptr<SDL_Renderer> wSDL::s_renderer;
std::shared_ptr<SDL_Surface> wSDL::s_screen_surface;



sdl_unique_texture make_unique_texture(SDL_Texture *t) {return sdl_unique_texture(t);}
sdl_unique_mix_chunk make_unique_mix_chunk(Mix_Chunk *c) {return sdl_unique_mix_chunk(c);}
sdl_unique_font make_unique_font(TTF_Font *f) {return sdl_unique_font(f);}


bool wSDL::Init()
{
    if (wSDL::debug)
        printf("Initializing SDL!\n");
    bool success = true;

    try
    {
        // This line is only needed, if you want debug the program
        SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
            throw std::runtime_error("SDL could not initialize! SDL Error: " + std::string(SDL_GetError()) + "\n");

        if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            printf("Warning: Linear texture filtering not enabled!");

        s_window = sdl_shared(SDL_CreateWindow("Cpp-ProjectV2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                wSDL::SCREEN_WIDTH, wSDL::SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
        if (!s_window)
            throw std::runtime_error("Window could not be created! SDL Error: " + std::string(SDL_GetError()) + "\n");

        s_renderer = sdl_shared(SDL_CreateRenderer(s_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
        if (s_renderer == nullptr)
            throw std::runtime_error("Renderer could not be created! SDL Error: " + std::string(SDL_GetError()) + "\n");

        SDL_SetRenderDrawColor(s_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

        if (!(IMG_Init(wSDL::IMG_FLAGS) & wSDL::IMG_FLAGS))
            throw std::runtime_error("SDL_image could not initialize! SDL_image Error: " + std::string(IMG_GetError()) + "\n");
        else
            wSDL::s_screen_surface = sdl_shared(SDL_GetWindowSurface(wSDL::s_window.get()));

        if (TTF_Init() < 0)
            throw std::runtime_error("SDL_ttf could not initialize! SDL_ttf error: " + std::string(TTF_GetError()) + "\n");

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            throw std::runtime_error("SDL_mixer could not initialize! SDL_mixer Error: " + std::string(Mix_GetError()) + "\n");
    }
    catch (std::exception &e)
    {
        success = false;
        printf("Failed to initialize SDL! Error: %s\n", e.what());
    }

    return success;
}

bool wSDL::LoadMedia()
{
    if (wSDL::debug)
        printf("Loading Media!\n");
    return wResources::Load();
}

void wSDL::Close()
{
    if (wSDL::debug)
        printf("Closing SDL!\n");
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    TTF_Quit();
}

bool wSDL::CheckCollision(const Rect<double> &a, const Rect<double> &b)
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

Point<double> wSDL::Distance(const Rect<double> &a, const Rect<int> &b)
{
    return wSDL::Distance(a, b.ToDouble()).ToDouble();
}

double wSDL::GetAngle(const Point<double> &a, const Point<double> &b)
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

Rect<int> wSDL::SDL_RectToIntRect(const SDL_Rect &r)
{
    Rect<int> new_r = {r.x, r.y, r.w, r.h};
    return new_r;
}

double wSDL::Constrain(double val, double min_val, double max_val)
{
    return std::fmin(std::fmax(val, min_val), max_val);
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

void wSDL::SDL_DelRes(SDL_Window   *r) {if (r != nullptr)SDL_DestroyWindow(r);}
void wSDL::SDL_DelRes(SDL_Renderer *r) {if (r != nullptr)SDL_DestroyRenderer(r);}
void wSDL::SDL_DelRes(SDL_Texture  *r) {if (r != nullptr)SDL_DestroyTexture(r);}
void wSDL::SDL_DelRes(SDL_Surface  *r) {if (r != nullptr)SDL_FreeSurface(r);}
void wSDL::SDL_DelRes(TTF_Font     *r) {if (r != nullptr)TTF_CloseFont(r);}
void wSDL::SDL_DelRes(Mix_Chunk    *r) {if (r != nullptr)Mix_FreeChunk(r);}
