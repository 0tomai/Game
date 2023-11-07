#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "reader.h"
#include "image.h"

void read(SDL_Renderer* renderer) {

    char c;
    FILE* f;
    f = fopen("map.txt", "rt");

    // while ((c = fgetc(f)) != EOF) {
    //     printf("e");
    // }
    int x = 0; 
    int y = 0; 

    while ((c = fgetc(f)) != EOF) {
        if (c == '1') {
            // Charger et afficher l'image
            SDL_Texture* image = charger_image("font.bmp", renderer);

            // Afficher l'image à la position x, y
            SDL_Rect destRect = {x, y, 0, 0}; 
            SDL_QueryTexture(image, NULL, NULL, &destRect.w, &destRect.h);
            SDL_RenderCopy(renderer, image, NULL, &destRect);

            x += destRect.w; 

            SDL_DestroyTexture(image);
        } else if (c == '\n') {
            x = 0;
            y += 100;
        } else 
        {
            x = 0;
            y += 100;
        }
    }
    

    fclose(f);
}
