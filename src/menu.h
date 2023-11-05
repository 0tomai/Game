#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

struct menu
{
    SDL_Texture* j;
    SDL_Texture* c;
    SDL_Texture* fond;
    TTF_Font* font;
    SDL_Color color;
    SDL_Rect jouer, credit;
    int state;


}; typedef struct menu menu_t;

SDL_Renderer* init_menu(SDL_Window* f, menu_t* m);
    
void refresh_menu(SDL_Renderer* f, menu_t* m);

void free_menu(menu_t* m);

void handle_menu(SDL_Event* e, menu_t* m);

#endif