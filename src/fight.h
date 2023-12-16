#ifndef COMBAT_H
#define COMBAT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "jeu.h"
#include "enemy.h"
#include "image.h"


typedef enum {
    COMBAT_IDLE,
    COMBAT_PLAYER_TURN,
    COMBAT_ENEMY_TURN,
    COMBAT_OVER
} CombatState;

void startCombat(SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t** head, SDL_Rect *enemies, int *nbEnemies, int index, jeu_t *game, SDL_Texture* enemyTexture, SDL_Texture*playerTexture);
void renderCombatUI(SDL_Renderer *renderer, player_t *player, enemy_t *enemy, SDL_Texture*playerTexture, SDL_Texture* enemyTexture);
void handlePlayerAttack(CombatState* combatState,enemy_t *enemy);
void handleEnemyAttack(CombatState* combatState, player_t *player);
bool isCombatOver(player_t *player, enemy_t *enemy);
void refresh_fight(CombatState* combatState, SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t **head, SDL_Rect *enemies, int *nbEnemies, int index, jeu_t *game, SDL_Texture* enemyTexture, SDL_Texture*playerTexture);
void renderGameOverText(SDL_Renderer *renderer);
#endif // COMBAT_H
