#ifndef CREDIT_H
#define CREDIT_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

struct credit
{
    SDL_Texture* j;
    SDL_Texture* c;
    SDL_Texture* fond;
    TTF_Font* font;
    SDL_Color color;
    SDL_Rect jouer, credit;
    int state;


}; typedef struct credit credit_t;

SDL_Renderer* init_credit(credit_t* c, SDL_Renderer* r);
    
void refresh_credit(SDL_Renderer* f, credit_t* c);

void free_credit(credit_t* c);

void handle_credit(SDL_Event* e, credit_t* c);

#endif