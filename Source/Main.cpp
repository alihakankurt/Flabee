#include <SDL3/SDL.h>

const char* Title = "Flabee";
constexpr int WindowWidth = 1280;
constexpr int WindowHeight = 720;

int main(int argc, const char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization Failure", "Unable to initialize SDL", nullptr);
        return 1;
    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    if (!SDL_CreateWindowAndRenderer(Title, WindowWidth, WindowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window/Renderer Creation Failure", "Unable to create window or renderer", nullptr);
        return 1;
    }

    SDL_SetRenderLogicalPresentation(renderer, WindowWidth, WindowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        const SDL_FRect rect{0,0,30,30};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
