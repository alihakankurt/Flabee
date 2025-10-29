#include <Constants.h>
#include <Bee.h>
#include <Obstacle.h>
#include <Collision.h>
#include <SDL3/SDL.h>

int main(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization Failure", "Unable to initialize SDL", 0);
        return 1;
    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window/Renderer Creation Failure", "Unable to create window or renderer", 0);
        return 1;
    }

    SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    Bee bee;
    Bee_Initialize(&bee);

    ObstacleList obstacles = {0};

    Uint64 previousTicks = SDL_GetTicksNS();
    bool running = true;
    while (running)
    {
        Uint64 currentTicks = SDL_GetTicksNS();
        float deltaTime = (currentTicks - previousTicks) / 1000000000.0f;
        previousTicks = currentTicks;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    Bee_Jump(&bee);
                    break;
            }
        }

        Bee_Update(&bee, deltaTime);
        Obstacles_Update(&obstacles, deltaTime);

        if (IsCollide(&bee, &obstacles))
        {
            SDL_SetRenderDrawColor(renderer, 100, 0, 100, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }

        SDL_RenderClear(renderer);

        Bee_Draw(&bee, renderer);
        Obstacles_Draw(&obstacles, renderer);

        SDL_RenderPresent(renderer);
    }

    Obstacles_Free(&obstacles);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
