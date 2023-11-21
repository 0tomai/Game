#include "jeu.h"


SDL_Renderer* init_jeu(jeu_t* m, SDL_Renderer* r, player_t* p){
    SDL_RenderClear(r);
    m->play = p;
    m->state = 0;
    m->fond = charger_image("src/fond_jeu.bmp", r);
    
    return r;
}

void refresh_jeu(SDL_Renderer* r, jeu_t* c, SDL_Texture* texture, SDL_Texture* ch, char map[], SDL_Rect* rec, int nbUn, SDL_Rect* play, SDL_Texture* playerText){
        SDL_Delay(10);
        SDL_RenderClear(r);
        SDL_RenderCopy(r, c->fond, NULL, NULL);
        printPlayer(c->play, r, play, playerText);
        //reading(r, texture, ch, map, rec);
        for(int i =0; i<nbUn; i++){
            SDL_RenderCopy(r, texture, NULL, &rec[i]);
        }
        SDL_RenderPresent(r);
}

void free_jeu(jeu_t* c){
    SDL_DestroyTexture(c->fond);
    free(c);
}

void handle_jeu(SDL_Event* e, jeu_t* c, SDL_Rect* rec, int nbUn, float dt){
    //SDL_PollEvent(&e);
    //int mx=0, my=0;
    switch (e->type)
    {
        case SDL_KEYDOWN: //gestion souris
                switch (e->key.keysym.sym)
                {
                case SDLK_RIGHT:
                    //printf("going right\n");
                    update(rec, nbUn, 0, dt);
                    break;
                case SDLK_LEFT:
                    //printf("going left\n");
                    update(rec, nbUn, 1, dt);
                    break;
                case SDLK_UP:
                    printf("going up\n");
                    update(rec, nbUn, 2, dt);
                    break;
                case SDLK_DOWN:
                    printf("going down\n");
                    update(rec, nbUn, 3,dt);
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
void update(SDL_Rect* r, int nbUn, int dg, float dt){
    if(dg == 0){
        for(int i = 0; i < nbUn; i++){
            r[i].x = r[i].x-500 * dt;
        }
    }
    if(dg == 1){
        for(int i = 0; i < nbUn; i++){
            r[i].x = r[i].x+500*dt;
        }
    }
    if(dg == 2){
        for(int i = 0; i < nbUn; i++){
            r[i].y = r[i].y+10;
        }
    }
    if(dg == 3){
        for(int i = 0; i < nbUn; i++){
            r[i].y = r[i].y-10;
        }
    }
}