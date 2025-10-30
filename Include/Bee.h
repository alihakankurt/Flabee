#ifndef __FLABEE_BEE__
#define __FLABEE_BEE__

#include <SDL3/SDL_render.h>

typedef struct Bee
{
    float PositionY;
    float VelocityY;
} Bee;

void Bee_Initialize(Bee* bee);
void Bee_Update(Bee* bee, float deltaTime);
void Bee_Jump(Bee* bee);
void Bee_Draw(const Bee* bee, SDL_Renderer* renderer);

#endif
