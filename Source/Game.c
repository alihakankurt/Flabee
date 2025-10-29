#include <Game.h>
#include <Constants.h>
#include <Collision.h>
#include <stdbool.h>

bool Game_Initialize(Game* game)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization Failure", "Unable to initialize SDL", 0);
        return false;
    }

    if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &game->Window, &game->Renderer))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Window/Renderer Creation Failure", "Unable to create window or renderer", 0);
        return false;
    }

    SDL_SetRenderLogicalPresentation(game->Renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    Bee_Initialize(&game->Beee);
    game->Obstacles = (ObstacleList){0};
    game->BestScore = 0;

    return true;
}

void Game_Finalize(Game* game)
{
    Obstacles_Free(&game->Obstacles);

    SDL_DestroyRenderer(game->Renderer);
    SDL_DestroyWindow(game->Window);
}

void Game_Update(Game* game, float deltaTime)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                game->Running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                Bee_Jump(&game->Beee);
                break;
        }
    }

    Bee_Update(&game->Beee, deltaTime);
    game->Score += Obstacles_Update(&game->Obstacles, deltaTime);
}

void Game_Render(Game* game)
{
    if (IsCollide(&game->Beee, &game->Obstacles))
    {
        SDL_SetRenderDrawColor(game->Renderer, 100, 0, 100, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(game->Renderer, 0, 0, 0, 255);
    }

    SDL_RenderClear(game->Renderer);

    Bee_Draw(&game->Beee, game->Renderer);
    Obstacles_Draw(&game->Obstacles, game->Renderer);

    SDL_RenderPresent(game->Renderer);
}

int Game_Run()
{
    Game game;
    if (!Game_Initialize(&game))
    {
        return 1;
    }

    Uint64 previousTicks = SDL_GetTicksNS();
    while (game.Running)
    {
        Uint64 currentTicks = SDL_GetTicksNS();
        float deltaTime = (currentTicks - previousTicks) / 1000000000.0f;
        previousTicks = currentTicks;
        Game_Update(&game, deltaTime);
        Game_Render(&game);
    }

    Game_Finalize(&game);
    return 0;
}
