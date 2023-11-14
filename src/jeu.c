#include "jeu.h"


SDL_Renderer* init_jeu(jeu_t* m, SDL_Renderer* r){
    SDL_RenderClear(r);

    // Charger l’image

    m->state = 0;
    m->fond = charger_image("src/fond_jeu.bmp", r);

    return r;
}

void refresh_jeu(SDL_Renderer* r, jeu_t* c){
        SDL_Delay(33);
        SDL_RenderClear(r);
        SDL_RenderCopy(r, c->fond, NULL, NULL);
        reading(r);
        SDL_RenderPresent(r);
}

void free_jeu(jeu_t* c){
    SDL_DestroyTexture(c->fond);
    free(c);
}

void handle_jeu(SDL_Event* e, jeu_t* c){
    //SDL_PollEvent(&e);
    int mx=0, my=0;
    switch (e->type)
    {
        case SDL_KEYDOWN: //gestion souris
                switch (e->key.keysym.sym)
                {
                case SDLK_RIGHT:
                    printf("going right\n");

                    break;
                case SDLK_LEFT:
                    printf("going left\n");
                    break;

                case SDLK_SPACE:
                    printf("jump\n");
                    break;
                case SDLK_p:
                    c->state = 1;
                default:
                    break;
                }
                break;
    }
}