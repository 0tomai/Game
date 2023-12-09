#include "checkpoint.h"

void printChp(SDL_Rect* r, SDL_Renderer* render, SDL_Texture* texture){
    SDL_RenderCopy(render, texture, NULL, r);
}