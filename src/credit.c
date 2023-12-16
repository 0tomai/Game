#include "credit.h"
#include "image.h"

SDL_Renderer* init_credit(credit_t* m, SDL_Renderer* r){
    SDL_RenderClear(r);

    // Charger l’image

    m->state = 0;
    m->fond = charger_image("src/telechargement.bmp", r);


    m->jouer.h = 60;
    m->jouer.w = 800;
    m->jouer.x = 225;
    m->jouer.y = 200;
    m->credit.h = 100;
    m->credit.w = 300;
    m->credit.x = 490;
    m->credit.y = 400;
    
    //SDL_SetRenderDrawColor(ecran, 255, 0, 0, 255);
    //SDL_RenderFillRect(ecran, &jouer); 
    //SDL_RenderFillRect(ecran, &credit);  
    TTF_Init();
    m->font = TTF_OpenFont("src/arial.ttf",28);
    SDL_Color cc = {0, 0, 0, 0};
    m->color = cc;
    m->j = charger_texte("Un jeu incroyable cree par des gens incroyables !", r, m->font, m->color);
    m->c = charger_texte("Retour", r, m->font, m->color);
    SDL_QueryTexture(m->j, NULL, NULL, NULL, NULL);
    SDL_QueryTexture(m->c, NULL, NULL, NULL, NULL);
    return r;
}

void refresh_credit(SDL_Renderer* r, credit_t* c){
        SDL_Delay(33);
        SDL_RenderClear(r);
        SDL_RenderCopy(r, c->fond, NULL, NULL);
        SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(r, 255, 255, 255, 100);
        SDL_RenderFillRect(r, &c->jouer); 
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);

        SDL_RenderFillRect(r, &c->credit);
        SDL_RenderCopy(r, c->j, NULL, &c->jouer);
        SDL_RenderCopy(r, c->c, NULL, &c->credit);

        SDL_RenderPresent(r);
}

void free_credit(credit_t* c){
    if (c->state != -1)
    {
        SDL_DestroyTexture(c->fond);
        SDL_DestroyTexture(c->j);
        SDL_DestroyTexture(c->c);
    }
    
    
    free(c);
}

void handle_credit(SDL_Event* e, credit_t* c){
    //SDL_PollEvent(&e);
    int mx=0, my=0;
    switch (e->type)
    {
        case SDL_MOUSEBUTTONDOWN: //gestion souris
                if (e->button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mx, &my);
                    if ((mx >= 490 && mx <= 790) && (my >= 400 && my <= 500))
                    {
                        c->state = 1;
                        printf("Crédit, etat credit: %d\n", c->state);
                    }
                }
                break;
    }
}