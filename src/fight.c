#include "fight.h"
#include <stdio.h>

void startCombat(SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t **head, SDL_Rect *enemies, int *nbEnemies, int index, jeu_t *game, SDL_Texture* enemyTexture, SDL_Texture *playerTexture) {
    srand(time(NULL));
    //printf("FIGHT %d\n", player->isFighting);

    CombatState combatState = COMBAT_IDLE;
    //printf("HP ENNEMI D2B : %d \n", enemy->hp);
    refresh_fight(&combatState, renderer, player, enemy, head, enemies, nbEnemies, index, game, enemyTexture, playerTexture);
    
}
void refresh_fight(CombatState* combatState, SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t **head, SDL_Rect *enemies, int *nbEnemies, int index, jeu_t *game, SDL_Texture* enemyTexture, SDL_Texture *playerTexture)
{
    while (*combatState != COMBAT_OVER) {
     
        SDL_Event event;
        SDL_PollEvent(&event);
        renderCombatUI(renderer, player, enemy, playerTexture, enemyTexture);

        switch (*combatState) {
            case COMBAT_IDLE:
                *combatState = COMBAT_PLAYER_TURN;
                break;

            case COMBAT_PLAYER_TURN:
                if (enemy->hp <= 0) {
                    *combatState = COMBAT_OVER;
                    removeEnemy(head, enemy, enemies, nbEnemies, index);
                    player->isFighting = 0;
                    return;
                }else if (player->hp <= 0)
                {
                    //printf("OVER\n");
                    *combatState = COMBAT_OVER;
                    game->state = 2;
                    //renderGameOverText(renderer);
                    player->isFighting = 0;
                }else {
                handlePlayerAttack(combatState, renderer, player, enemy, head, enemies, nbEnemies, index);
                }
                break;

            case COMBAT_ENEMY_TURN:
                if (enemy->hp <= 0) {
                    *combatState = COMBAT_OVER;
                    removeEnemy(head, enemy, enemies, nbEnemies, index);
                    player->isFighting = 0;
                    return;
                }else if (player->hp <= 0)
                {
                    *combatState = COMBAT_OVER;
                    game->state = 2;
                    //renderGameOverText(renderer);
                }else {
                handleEnemyAttack(combatState, renderer, player, enemy, head, enemies, nbEnemies, index);
                }
                break;

            case COMBAT_OVER:
                break;
        }
    }
}
void renderCombatUI(SDL_Renderer *renderer, player_t *player, enemy_t *enemy, SDL_Texture *playerTexture, SDL_Texture *enemyTexture) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int maxHealth = 100;

    int playerHealthWidth = (player->hp * 100) / maxHealth;
    int enemyHealthWidth = (enemy->hp * 100) / maxHealth;

    // Render player health bar
    SDL_Rect playerHealthBar = {10, 10, playerHealthWidth, 20};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &playerHealthBar);

    // Render player texture
    SDL_Rect playerRect = {400, 450, 100, 100};
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

    // Render enemy health bar
    SDL_Rect enemyHealthBar = {1390 - enemyHealthWidth, 10, enemyHealthWidth, 20};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_RenderFillRect(renderer, &enemyHealthBar);

    // Render enemy texture
    SDL_Rect enemyRect = {900, 500, 50, 50}; 
    SDL_RenderCopy(renderer, enemyTexture, NULL, &enemyRect);

    SDL_RenderPresent(renderer);
}

// Player Turn
void handlePlayerAttack(CombatState* combatState, SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t *head, SDL_Rect *enemies, int *nbEnemies, int index) {
    SDL_Event event;
    SDL_PollEvent(&event);
    //renderCombatUI(renderer, player, enemy);
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_a: // Change 'a' to the key you want to use for attacking
                // Randomize player attack power within a range (e.g., 15 to 25)
                int playerAttackPower = rand() % 21 + 80; 

                // Add a chance to dodge (e.g., 20% chance to dodge)
                int dodgeChance = rand() % 100;
                if (dodgeChance < 20) {
                    printf("Enemy dodged the attack!\n");
                } else {
                    enemy->hp -= playerAttackPower;
                    printf("Player attacks! Enemy health: %d\n", enemy->hp);
                }

                *combatState = COMBAT_ENEMY_TURN;
                //refresh_fight(combatState, renderer, player, enemy, head, enemies, nbEnemies, index);
                break;

            // Add cases for other keys if needed

            default:
                break;
        }
    }
}

//Enemy Turn
void handleEnemyAttack(CombatState* combatState, SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t *head, SDL_Rect *enemies, int *nbEnemies, int index) {
    // Randomize enemy attack power within a range (e.g., 10 to 20)
    int enemyAttackPower = rand() % 11 + 10;

    // Add a chance for the player to dodge (e.g., 30% chance to dodge)
    int dodgeChance = rand() % 100;
    if (dodgeChance < 30) {
        printf("Player dodged the attack!\n");
    } else {
        player->hp -= enemyAttackPower;
        printf("Enemy attacks! Player health: %f\n", player->hp);
    }

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
    SDL_Rect gameOverRect = {0, 0, 1400, 720};

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(gameOverTexture);
}

