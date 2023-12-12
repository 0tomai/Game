#include "fight.h"
#include <stdio.h>

void startCombat(SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t *head, SDL_Rect *enemies, int *nbEnemies, int index) {
    //printf("FIGHT %d\n", player->isFighting);

    CombatState combatState = COMBAT_IDLE;
    //printf("HP ENNEMI D2B : %d \n", enemy->hp);
    refresh_fight(&combatState, renderer, player, enemy, head, enemies, nbEnemies, index);
    
}
void refresh_fight(CombatState* combatState, SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t *head, SDL_Rect *enemies, int *nbEnemies, int index)
{
    while (*combatState != COMBAT_OVER) {
        SDL_Event event;
        SDL_PollEvent(&event);

        renderCombatUI(renderer, player, enemy);

        switch (*combatState) {
            case COMBAT_IDLE:
                *combatState = COMBAT_PLAYER_TURN;
                break;

            case COMBAT_PLAYER_TURN:

                if (enemy->hp <= 0) {
                    printf("OVER\n");
                    *combatState = COMBAT_OVER;
                    removeEnemy(&head, enemy, enemies, nbEnemies, index);
                    player->isFighting = 0;
                    //return;
                }else if (player->hp <= 0)
                {
                    printf("OVER\n");
                    *combatState = COMBAT_OVER;
                    renderGameOverText(renderer);
                    player->isFighting = 0;
                }else {
                handlePlayerAttack(combatState, renderer, player, enemy, head, enemies, nbEnemies, index);
                }
                break;

            case COMBAT_ENEMY_TURN:
                if (enemy->hp <= 0) {
                    printf("OVER\n");
                    *combatState = COMBAT_OVER;
                    removeEnemy(&head, enemy, enemies, nbEnemies, index);
                    player->isFighting = 0;
                    return;
                }else if (player->hp <= 0)
                {
                    printf("OVER\n");
                    *combatState = COMBAT_OVER;
                    renderGameOverText(renderer);
                }else {
                handleEnemyAttack(combatState, renderer, player, enemy, head, enemies, nbEnemies, index);
                }
                break;

            case COMBAT_OVER:
                break;
        }
    }
}
void renderCombatUI(SDL_Renderer *renderer, player_t *player, enemy_t *enemy) {

    //SDL_RenderClear(renderer);

    SDL_Rect playerHealthBar = {10, 10, player->hp, 20};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &playerHealthBar);

    SDL_Rect enemyHealthBar = {50, 10, enemy->hp, 20};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &enemyHealthBar);

    SDL_RenderPresent(renderer);
}

void handlePlayerAttack(CombatState* combatState, SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t *head, SDL_Rect *enemies, int *nbEnemies, int index) {
    

    int playerAttackPower = 20; 
    enemy->hp -= playerAttackPower;

    printf("Player attacks! Enemy health: %d\n", enemy->hp);

    *combatState = COMBAT_ENEMY_TURN;
    //refresh_fight(combatState, renderer, player, enemy, head, enemies, nbEnemies, index);
}

void handleEnemyAttack(CombatState* combatState, SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t *head, SDL_Rect *enemies, int *nbEnemies, int index) {
    int enemyAttackPower = 15;
    player->hp -= enemyAttackPower;

    printf("Enemy attacks! Player health: %f\n", player->hp);

    *combatState = COMBAT_PLAYER_TURN;
    //refresh_fight(combatState, renderer, player, enemy, head, enemies, nbEnemies, index);
}

bool isCombatOver(player_t *player, enemy_t *enemy) {
    return player->hp <= 0 || enemy->hp <= 0;
}

void renderGameOverText(SDL_Renderer *renderer) {
    SDL_Texture *gameOverTexture = charger_image("src/game_over_texture.bmp", renderer);

    int screenWidth, screenHeight;
    //SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
    //printf("%d, %d \n", screenHeight, screenWidth);
    SDL_Rect gameOverRect = {0, 0, 1280, 720};

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
    SDL_RenderPresent(renderer);

    printf("FINI\n");

    SDL_Delay(30);
    SDL_DestroyTexture(gameOverTexture);
}

