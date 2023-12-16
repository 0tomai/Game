#include "menu.h"
#include "image.h"

//Fonction qui initialise le renderer et associe à celui-ci les éléments initialisés du menu
SDL_Renderer* init_renderer(SDL_Window* f, menu_t* m){
    SDL_Renderer* r = SDL_CreateRenderer(f, -1, SDL_RENDERER_ACCELERATED);

    m->state = 0;
    m->fond = charger_image("src/fond_menu.bmp", r);
    m->jouer.h = 100;
    m->jouer.w = 300;
    m->jouer.x = 490;
    m->jouer.y = 200;
    m->credit.h = 100;
    m->credit.w = 300;
    m->credit.x = 490;
    m->credit.y = 400;
     
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

//Fonction qui permet de revenir au menu lorsqu'un autre affichage (jeu ou crédit) a été associé au renderer
SDL_Renderer* back2menu(menu_t* m, SDL_Renderer* r){
    SDL_RenderClear(r);

    m->state = 0;
    m->fond = charger_image("src/fond_menu.bmp", r);


    m->jouer.h = 100;
    m->jouer.w = 300;
    m->jouer.x = 490;
    m->jouer.y = 200;
    m->credit.h = 100;
    m->credit.w = 300;
    m->credit.x = 490;
    m->credit.y = 400;
     
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

//Fonction pour update le menu
void refresh_menu(SDL_Renderer* r, menu_t* m){
        
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

void handle_menu(SDL_Event* e, menu_t* m){
    //SDL_PollEvent(&e);
    int mx=0, my=0;
    switch (e->type)
    {
        case SDL_MOUSEBUTTONDOWN: //gestion souris
                if (e->button.button == SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&mx, &my);
                    if ((mx >= 490 && mx <= 790) && (my >= 200 && my <= 300))
                    {
                        m->state = 1;
                        printf("Jouer, etat menu: %d\n", m->state);
                    }
                    if ((mx >= 490 && mx <= 790) && (my >= 400 && my <= 500))
                    {
                        m->state = 2;
                        printf("Crédit, etat menu: %d\n", m->state);
                    }
                }
                break;
    }
}
