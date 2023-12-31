#include "player.h"

#define GRAVITY 100
#define JUMP_VELOCITY 100.0 

player_t* initPlayer(player_t *p, float x, int y)
{
        p->posX = x;
        p->posY = y;
        p->velocity = 0;
        p->dirX = 0;
        p->is_jumping = 0; 
        p->timer = 20;
        p->nbJump = 0;
        p->nbJumpCan = 3;
        p->hp = 100;
        p->isFighting = 0;
    return p;
}
void printPlayer(player_t *p, SDL_Renderer* renderer, SDL_Rect* destRect, SDL_Texture* texture)
{

        destRect->x = p->posX;
        destRect->y = p->posY;
        destRect->w = 32;
        destRect->h = 32;

    SDL_RenderCopy(renderer, texture, NULL, destRect);
}

void updatePlayerPosition(player_t *p, float deltaTime)
{
    p->posX += p->velocity * deltaTime * p->dirX;

}

void gravity(SDL_Rect rects[], int numRects, float deltaTime, player_t*p)
{
    for (int i = 0; i <= numRects; i++)
    {
        rects[i].y -= (GRAVITY- p->velocity) * deltaTime;
    }
}

void jump(SDL_Rect rects[], int numRects, float deltaTime)
{
    for (int i = 0; i < numRects; i++)
    {
        rects[i].y += JUMP_VELOCITY * deltaTime +100;

    }
}
void move(player_t *p, int dir)
{
    if (p->dirX != dir) {
        p->dirX = dir;
    }
}


