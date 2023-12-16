#include "checkpoint.h"

//procedure d'affichage du checkpoint d'arrivée
void printChp(SDL_Rect* r, SDL_Renderer* render, SDL_Texture* texture){
    SDL_RenderCopy(render, texture, NULL, r);
}