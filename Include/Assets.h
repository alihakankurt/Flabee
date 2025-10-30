#ifndef __FLABEE_ASSETS__
#define __FLABEE_ASSETS__

#include <stdbool.h>
#include <SDL3/SDL_render.h>

struct Assets
{
    SDL_Texture* Background;
    SDL_Texture* Bee;
    SDL_Texture* Obstacle;
};

extern struct Assets Assets;

bool Assets_Load(SDL_Renderer* renderer);
void Assets_Unload();

#endif
