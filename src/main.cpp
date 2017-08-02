#include "wSDL.h"
#include <stdio.h>
#include "Map.h"

int main(int argc, char* args[])
{
    if (!wSDL::Init())
    {
        printf("Failed to Initialize!\n");
        return 1;
    }

    Map board = Map("resources/jewon.map");

    if (!wSDL::LoadMedia(board))
    {
        printf("Failed to load media!\n");
    }
    else
    {
        bool quit = false;

        SDL_Event e;

        while (!quit)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                    quit = true;

                if (board.HandleEvent(e))
                    quit = true;
            }

            board.MovePlayer();
            board.SetCamera();

            wSDL::ClearScreen();

            board.Render();

            wSDL::UpdateScreen();
        }

        wSDL::Close(board);
    }

    return 0;
}
