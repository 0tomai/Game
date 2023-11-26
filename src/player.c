#include "player.h"

#define GRAVITY 100.0
#define JUMP_VELOCITY 2000.0 

player_t* initPlayer(player_t *p, float x, int y)
{
        p->posX = x;
        p->posY = y;
        p->velocity = 100;
        p->dirX = 0;
    return p;
}
void printPlayer(player_t *p, SDL_Renderer* renderer, SDL_Rect* destRect, SDL_Texture* texture)
{
    // SDL_Texture* texture = charger_image("src/player.bmp", renderer);
    // if (texture == NULL) {
    // fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    // }

    // SDL_Rect destRect;
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

void gravity(SDL_Rect rects[], int numRects, float deltaTime)
{
    for (int i = 0; i < numRects; i++)
    {
        rects[i].y -= GRAVITY * deltaTime;
        //printf("%d\n", rects[i].y);

    }
}

void jump(SDL_Rect rects[], int numRects, float deltaTime)
{
    for (int i = 0; i < numRects; i++)
    {
        rects[i].y += JUMP_VELOCITY * deltaTime +100;
        //printf("%d\n", rects[i].y);

    }
}
void move(player_t *p, int dir)
{
    if (p->dirX != dir) {
        p->dirX = dir;
    }
}


