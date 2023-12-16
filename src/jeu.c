#include "jeu.h"
#include <stdbool.h>

//clear le renderer et initialise le jeu 
SDL_Renderer* init_jeu(jeu_t* m, SDL_Renderer* r, player_t* p){
    SDL_RenderClear(r);
    m->play = p;
    m->state = 0;
    m->fond = charger_image("src/fond_jeu.bmp", r);
    
    return r;
}
//Fonction de rafraichissement de l'affichage du jeu
void refresh_jeu(SDL_Renderer* r, jeu_t* c, SDL_Texture* texture, SDL_Texture* ch, SDL_Rect* rec, int nbUn, SDL_Rect* play, SDL_Rect* chp, SDL_Texture* playerText){
        SDL_RenderClear(r);
        SDL_RenderCopy(r, c->fond, NULL, NULL);
        printPlayer(c->play, r, play, playerText);
        printChp(chp, r, ch);
        for(int i =0; i<nbUn; i++){
            
            SDL_RenderCopy(r, texture, NULL, &rec[i]);
        }

}

//Libère la mémoire allouée au jeu
void free_jeu(jeu_t* c){
    if (c->state!=-1)
    {
        SDL_DestroyTexture(c->fond);
    }
    
    free(c);
}
