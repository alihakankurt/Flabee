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

        SDL_Quit();
        return false;
    }

    SDL_SetRenderLogicalPresentation(game->Renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    if (!Assets_Load(game->Renderer))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Asset Load Failure", "An asset could not be loaded correctly", 0);

        SDL_DestroyRenderer(game->Renderer);
        game->Renderer = NULL;

        SDL_DestroyWindow(game->Window);
        game->Window = NULL;

        SDL_Quit();
        return false;
    }

    Bee_Initialize(&game->Beee);
    game->Obstacles = (ObstacleList){0};
    game->BestScore = 0;

    return true;
}

void Game_Finalize(Game* game)
{
    Obstacles_Free(&game->Obstacles);

    Assets_Unload();

    SDL_DestroyRenderer(game->Renderer);
    game->Renderer = NULL;

    SDL_DestroyWindow(game->Window);
    game->Window = NULL;

    SDL_Quit();
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

    if (IsCollide(&game->Beee, &game->Obstacles))
    {
        Bee_Initialize(&game->Beee);
        Obstacles_Free(&game->Obstacles);
        if (game->Score > game->BestScore)
        {
            game->BestScore = game->Score;
        }

        game->Score = 0;
    }
}

void Game_Render(Game* game)
{
    SDL_SetRenderDrawColor(game->Renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->Renderer);

    SDL_RenderTexture(game->Renderer, Assets.Background, NULL, NULL);

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
