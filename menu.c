#include "menu.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "image.h"
#include <SDL2/SDL_ttf.h>

void afficherMenu(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    // Chargement de l'image et affichage
    SDL_Texture* imageTexture = charger_image("téléchargement.bmp", renderer);
    if (imageTexture != NULL) {
        SDL_Rect imageRect; 
        imageRect.x = 0; 
        imageRect.y = 0; 
        imageRect.w = 700;
        imageRect.h = 400;

        SDL_RenderCopy(renderer, imageTexture, NULL, &imageRect);
        SDL_DestroyTexture(imageTexture);
    }

    // Option du menu
    SDL_Rect option1Rect = {100, 100, 200, 50};
    SDL_Rect option2Rect = {100, 200, 200, 50};
    SDL_Rect option3Rect = {100, 300, 200, 50};

    // Dessinez les options de menu
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur du texte
    SDL_RenderFillRect(renderer, &option1Rect);
    SDL_RenderFillRect(renderer, &option2Rect);
    SDL_RenderFillRect(renderer, &option3Rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Couleur du fond
    SDL_RenderDrawRect(renderer, &option1Rect);
    SDL_RenderDrawRect(renderer, &option2Rect);
    SDL_RenderDrawRect(renderer, &option3Rect);


    // Dessinez le texte à l'intérieur des options
    TTF_Font *police = TTF_OpenFont("SIXTY.TTF", 24);
    const char *texte = "Play";
    SDL_Color couleur = { 255, 255, 255, 255 };

    SDL_Surface *surfaceTexte = TTF_RenderText_Solid(police, texte, couleur);
    if (surfaceTexte != NULL) {
        SDL_Texture *textureTexte = SDL_CreateTextureFromSurface(renderer, surfaceTexte);
        SDL_FreeSurface(surfaceTexte);

        if (textureTexte != NULL) {
            SDL_Rect destRect = { 100, 100, surfaceTexte->w, surfaceTexte->h };

            SDL_RenderCopy(renderer, textureTexte, NULL, &destRect);
            SDL_DestroyTexture(textureTexte);
        }
    }
    // Utilisez SDL_Renderer pour écrire le texte à l'emplacement approprié
}

int gererMenu(SDL_Renderer *renderer) {
    bool terminer = false;
    SDL_Event evenements;

    while (!terminer) {
        SDL_RenderClear(renderer);
        afficherMenu(renderer);

        SDL_RenderPresent(renderer);
        SDL_PollEvent(&evenements);

        switch (evenements.type) {
            case SDL_QUIT:
                terminer = true;
                break;
            case SDL_KEYDOWN:
                switch (evenements.key.keysym.sym) {
                    // Gérez les entrées clavier pour sélectionner des options
                    // par exemple, flèches haut/bas pour naviguer dans le menu
                }
                break;
        }
    }

    // Renvoyez la valeur correspondant à l'option sélectionnée ou au choix de quitter
    return EXIT_SUCCESS; // Remplacez cela par la valeur de retour appropriée
}
