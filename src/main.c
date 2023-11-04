#include "image.h"
#include "menu.h"
#include <stdbool.h>

int main()
{
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

    ecran = init_menu(window, m);
    // ecran = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // // Charger l’image
    // SDL_Texture* fond = charger_image("src/fond_menu.bmp", ecran);
    // SDL_Rect jouer, credit;
    // jouer.h = 100;
    // jouer.w = 300;
    // jouer.x = 490;
    // jouer.y = 200;
    // credit.h = 100;
    // credit.w = 300;
    // credit.x = 490;
    // credit.y = 400;
    
    // //SDL_SetRenderDrawColor(ecran, 255, 0, 0, 255);
    // //SDL_RenderFillRect(ecran, &jouer); 
    // //SDL_RenderFillRect(ecran, &credit);  
    // TTF_Init();
    // TTF_Font *font = TTF_OpenFont("src/arial.ttf",28);
    // SDL_Color color = {0,0,0,0};
    // SDL_Texture* j = charger_texte("Jouer", ecran, font, color);
    // SDL_Texture* c = charger_texte("Credits", ecran, font, color);
    // SDL_QueryTexture(j, NULL, NULL, NULL, NULL);
    // SDL_QueryTexture(c, NULL, NULL, NULL, NULL);

    bool terminer = false;
    SDL_Event evenements;
    int i = 0;
    while(!terminer){
        
        refresh_menu(ecran, m);
        //SDL_Delay(20);
        
        // SDL_RenderClear(ecran);
        // SDL_RenderCopy(ecran, fond, NULL, NULL);
        // SDL_SetRenderDrawColor(ecran, 255, 0, 0, 255);
        // SDL_RenderFillRect(ecran, &jouer); 
        // SDL_RenderFillRect(ecran, &credit);
        // SDL_RenderCopy(ecran, j, NULL, &jouer);
        // SDL_RenderCopy(ecran, c, NULL, &credit);
        i = i+1;
        // SDL_RenderPresent(ecran);
        SDL_PollEvent( &evenements );
        switch(evenements.type)
        {
            
            case SDL_MOUSEBUTTONDOWN:
                if (evenements.button.button == SDL_BUTTON_LEFT)
                {
                    printf("%d\n", i);
                }
                break;

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
    SDL_DestroyRenderer(ecran);

    SDL_DestroyWindow(window);
    //Quit:
    SDL_Quit();
    return statut;
}
