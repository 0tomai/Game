#include "player.h"

player_t* initPlayer(player_t *p, float x, int y)
{
        p->posX = x;
        p->posY = y;
        p->velocity = 100;
        p->dirX = 0;
    return p;
}
void printPlayer(player_t *p, SDL_Renderer* renderer)
{
     SDL_Texture* texture = charger_image("src/player.bmp", renderer);
    if (texture == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }

    SDL_Rect destRect;
        destRect.x = p->posX;
        destRect.y = p->posY;
        destRect.w = 8;
        destRect.h = 8;

    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void updatePlayerPosition(player_t *p, float deltaTime)
{
    p->posX += p->velocity * deltaTime * p->dirX;

}

void move(player_t *p, int dir)
{
    if (p->dirX != dir) {
        p->dirX = dir;
    }
}


