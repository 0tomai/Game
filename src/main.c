#include "image.h"
#include "menu.h"
#include "reader.h"
#include "credit.h"
#include <stdbool.h>

int main()
{
    int nbCol = 0;
    int nbLigne= 0;
    tailleFichier(&nbCol, &nbLigne);
    //printf("%d %d", nbCol, nbLigne);

    int** tab = init_tab(nbLigne, nbCol);
    fill_tab(tab);
    for (int i = 0; i < nbLigne; i++)
    {
        for (int j = 0; j < nbCol; j++)
        {
            printf("%d", tab[i][j]);
        }        
        printf("\n");
    }

    SDL_Window *window = NULL;
    int statut = EXIT_FAILURE;

    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());

        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    /* On agit sur la fenêtre ici */
    SDL_Renderer* ecran;

    menu_t* m = malloc(sizeof(menu_t));

    credit_t* c = malloc(sizeof(credit_t));

    c->state = -1;

    printf("%d", c->state);

    ecran = init_menu(window, m);

    bool terminer = false;
    
    SDL_Event evenements;
    int i = 0; //mx=0, my=0;
    while(!terminer){
        if (m->state == 0)
        {
            refresh_menu(ecran, m);
        }
        //printf("%d", m->state);
        if (m->state == 2 && c->state == -1)
        {
            ecran = init_credit(c, ecran);
        }
        if (c->state == 0)
        {
            refresh_credit(ecran, c);
        }
        if (c->state == 1)
        {
            back2menu(m, ecran);
            c->state = -1;
        }

        i = i+1;
        
        SDL_PollEvent( &evenements );
        if (m->state == 0)
        {
            handle_menu(&evenements, m);
        }
        if (c->state == 0 || c->state == 2)
        {
            handle_credit(&evenements, c);
        }
        
        
        

        switch(evenements.type)
        {

            case SDL_QUIT:
                terminer = true; 
                break;
            
            case SDL_KEYDOWN:
                switch(evenements.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        printf("%d\n", i);
                        break;
                    case SDLK_0:
                        terminer = false;
                        break;
                    case SDLK_ESCAPE:
                        case SDLK_q:
                            terminer = true; 
                            break;
                        break;
                    break;
                }  
        }
    }
    statut = EXIT_SUCCESS;
    // SDL_DestroyTexture(fond);
    free_menu(m);
    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(window);
    //Quit:
    SDL_Quit();
    return statut;
}
