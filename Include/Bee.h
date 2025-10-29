#ifndef __FLABEE_BEE__
#define __FLABEE_BEE__

#include <SDL3/SDL_render.h>

#define BEE_SIZE (WINDOW_WIDTH / 16.0f)
#define BEE_GRAVITY (WINDOW_HEIGHT * 1.4f)
#define BEE_JUMP_SPEED (WINDOW_HEIGHT * -0.7f)

typedef struct Bee
{
    float PositionX;
    float PositionY;
    float VelocityY;
} Bee;

void Bee_Initialize(Bee* bee);
void Bee_Update(Bee* bee, float deltaTime);
void Bee_Jump(Bee* bee);
void Bee_Draw(Bee* bee, SDL_Renderer* renderer);

#endif
