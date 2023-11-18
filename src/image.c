#include "image.h"

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer){
    SDL_Surface* wow = SDL_LoadBMP(nomfichier);
    SDL_Texture* res = SDL_CreateTextureFromSurface(renderer, wow);
    return res;
    
}
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer, TTF_Font *font, SDL_Color color){
    SDL_Surface* text = TTF_RenderText_Solid(font, message, color);
    SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, text);
    return t;
}

SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b){
    SDL_Surface* wow = SDL_LoadBMP(nomfichier);

    Uint32 chose = SDL_MapRGB(wow->format, r, g, b);
    SDL_SetColorKey(wow, SDL_TRUE , chose);
    SDL_Texture* res = SDL_CreateTextureFromSurface(renderer, wow);
    return res;
}