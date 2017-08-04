#include "wSDL.h"
#include <stdio.h>
#include "Map.h"
#include "LTimer.h"

int main(int argc, char* args[])
{
    if (!wSDL::Init())
    {
        printf("Failed to Initialize!\n");
        return 1;
    }

    if (!wSDL::LoadMedia())
    {
        printf("Failed to load media!\n");
        return 2;
    }

    else
    {
        bool quit = false;

        SDL_Event e;

        int frames = 0;
        LTimer step_timer, fps_timer;
        step_timer.Start();
        fps_timer.Start();

        Map board = Map("resources/jewon.map");

        while (!quit)
        {
            ++frames;
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                    quit = true;

                if (board.HandleEvent(e))
                    quit = true;
            }

            double time_step = step_timer.GetTicks() / 1000.0;

            board.MovePlayer(time_step);

            step_timer.Start();

            board.UpdateFPS(frames / (fps_timer.GetTicks() / 1000.0f));

            board.SetCamera();

            wSDL::ClearScreen();

            board.Render();

            wSDL::UpdateScreen();
        }

        wSDL::Close();
    }

    return 0;
}
