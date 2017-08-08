#include "wSDL.h"
#include <stdio.h>
#include "Map.h"
#include <deque>

int main(int argc, char* args[])
{
    if (!wSDL::Init())
    {
        return 1;
    }

    if (!wSDL::LoadMedia())
    {
        return 2;
    }

    else
    {
        if (wSDL::debug)
            printf("Starting Main Game...\n");
        {
            bool quit = false;

            SDL_Event e;

            int frames = 0;
            int fps_frames = 3;
            std::deque<uint32_t> ticks (fps_frames, 0);

            std::shared_ptr<Map> board = std::make_shared<Map>("resources/jewon.map");

            while (!quit)
            {
                ++frames;
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                        quit = true;

                    if (board->HandleEvent(e))
                        quit = true;
                }

                ticks.push_back(SDL_GetTicks());

                board->Update((ticks.at(1) - ticks.at(0)) / 1000.f);



                if (frames % fps_frames == 0)
                {
                    board->UpdateFPS(fps_frames / ((ticks.back() - ticks.front()) / 1000.f));
                }

                ticks.pop_front();

                board->SetCamera();

                wSDL::ClearScreen();

                board->Render();

                wSDL::UpdateScreen();
            }
            if (wSDL::debug)
                printf("Exiting main loop\n");
        }
        wSDL::Close();

    }

    return 0;
}
