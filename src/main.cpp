#include "wSDL.h"
#include <stdio.h>
#include "Map.h"
#include "LTimer.h"

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
            int fps_frames_chunk = 3;

            std::unique_ptr<LTimer> step_timer{new LTimer()};
            std::unique_ptr<LTimer> fps_timer{new LTimer()};
            step_timer->Start();
            fps_timer->Start();
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

                double time_step = step_timer->GetTicks() / 1000.0;

                board->MovePlayer(time_step);

                step_timer->Start();

                if (frames % fps_frames_chunk == 0)
                {
                    board->UpdateFPS(fps_frames_chunk / (fps_timer->GetTicks() / 1000.0f));
                    fps_timer->Start();
                }

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
