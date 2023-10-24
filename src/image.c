#include "image.h"

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer){
    SDL_Surface* wow = SDL_LoadBMP(nomfichier);
    SDL_Texture* res = SDL_CreateTextureFromSurface(renderer, wow);
    return res;
    
}