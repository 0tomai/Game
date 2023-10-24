#include "image.h"
#include <stdbool.h>

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    int statut = EXIT_FAILURE;

    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());

        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 400, SDL_WINDOW_SHOWN);
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    /* On agit sur la fenêtre ici */
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Charger l’image
    SDL_Texture* fond = charger_image("fond_menu.gif", ecran);
    bool terminer = false;
    SDL_Event evenements;
    while(!terminer){
        SDL_RenderClear(ecran);
        
        //SDL_PollEvent ...
        SDL_RenderPresent(ecran);
        SDL_PollEvent( &evenements );
        switch(evenements.type)
        {
            case SDL_QUIT:
                terminer = true; break;
            case SDL_KEYDOWN:
                switch(evenements.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        case SDLK_q:
                            terminer = true; break;
                }
        }
    statut = EXIT_SUCCESS;
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    //Quit:
    SDL_Quit();
    return statut;
    }
}
