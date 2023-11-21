#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "player.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Test Reading Function", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    player_t *p = malloc(sizeof(player_t));
    initPlayer(p, 20, 20);

    int quit = 0;
    SDL_Event e;
    Uint32 lastTime = SDL_GetTicks();
    float deltaTime;
    Uint32 currentTime = SDL_GetTicks();

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        move(p, -1);
                        break;
                    case SDLK_RIGHT:
                        move(p, 1);
                        break;
                }
            }
            else if(e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        p->dirX = 0;
                        break;
                    case SDLK_RIGHT:
                        p->dirX = 0;
                        break;
                }
            }
        }

        currentTime = SDL_GetTicks();
        deltaTime = (float)(currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        updatePlayerPosition(p, deltaTime);
        printf("deltatime : %f\n direction : %d\nposition : %d\n", deltaTime, p->dirX, p->posX);

        SDL_RenderClear(renderer);

        printPlayer(p, renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();


    return 0;
}
