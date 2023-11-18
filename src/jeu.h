#ifndef JEU_H
#define JEU_H

#include "reader.h"

struct jeu
{
    //SDL_Texture* j;
    //SDL_Texture* c;
    SDL_Texture* fond;
    //player_t* p;
    //TTF_Font* font;
    //SDL_Color color;
    //SDL_Rect jouer, credit;
    int state;


}; typedef struct jeu jeu_t;

SDL_Renderer* init_jeu(jeu_t* c, SDL_Renderer* r);
    
void refresh_jeu(SDL_Renderer* f, jeu_t* c, SDL_Texture* t, SDL_Texture* ch, char map[], SDL_Rect* rec, int nbUn);

void free_jeu(jeu_t* c);

void handle_jeu(SDL_Event* e, jeu_t* c, SDL_Rect* r, int nbUn);

void update(SDL_Rect* r, int nbun, int dg);

#endif