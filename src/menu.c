#include "menu.h"
#include "image.h"


SDL_Renderer* init_menu(SDL_Window* f, menu_t* m){
    SDL_Renderer* r = SDL_CreateRenderer(f, -1, SDL_RENDERER_ACCELERATED);

    // Charger l’image


    m->fond = charger_image("src/fond_menu.bmp", r);


    m->jouer.h = 100;
    m->jouer.w = 300;
    m->jouer.x = 490;
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
    m->j = charger_texte("Jouer", r, m->font, m->color);
    m->c = charger_texte("Credits", r, m->font, m->color);
    SDL_QueryTexture(m->j, NULL, NULL, NULL, NULL);
    SDL_QueryTexture(m->c, NULL, NULL, NULL, NULL);
    return r;
}

void refresh_menu(SDL_Renderer* r, menu_t* m){
        SDL_Delay(33);
        SDL_RenderClear(r);
        SDL_RenderCopy(r, m->fond, NULL, NULL);
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
        SDL_RenderFillRect(r, &m->jouer); 
        SDL_RenderFillRect(r, &m->credit);
        SDL_RenderCopy(r, m->j, NULL, &m->jouer);
        SDL_RenderCopy(r, m->c, NULL, &m->credit);

        SDL_RenderPresent(r);
}

void free_menu(menu_t* m){
    SDL_DestroyTexture(m->fond);
    SDL_DestroyTexture(m->j);
    SDL_DestroyTexture(m->c);
    free(m);
}
