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

    float positionX = WindowWidth / 20.0f;
    float positionY = WindowHeight / 2.0f;
    float velocityY = 0;

    float gravity = 800;
    float jumpSpeed = 300;

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
                    velocityY = -jumpSpeed;
                    break;
            }
        }

        velocityY += gravity * deltaTime;
        positionY += velocityY * deltaTime;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        const SDL_FRect rect{positionX,positionY,30,30};
        SDL_SetRenderDrawColor(renderer, 160, 160, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
