#include "player.h"

player_t* initPlayer(player_t *p, int x, int y)
{
    p->posX = x;
    p->posY = y;
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

    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}
