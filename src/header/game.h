#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "projectile.h"
#include "ennemie.h"
#include "wall.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_CHAR 64

// État global du jeu
typedef struct GameState {
  bool running;       // boucle principale active
  bool started;       // jeu lancé
  bool paused;        // pause activée
  int currentLevel;   // niveau actuel
} GameState;

// Init état du jeu
GameState *InitGameState();

// Affiche le fond
void GameBackground(SDL_Renderer *, SDL_Texture *);

// Boucle principale du jeu
void Game(SDL_Renderer *, Player *, Flechettes *, Canars *, Walls *, TTF_Font *, GameState *);

// Écran game over
void GameOver(SDL_Renderer *, SDL_Texture *, TTF_Font *, Player *);

// Écran d'accueil
void HomeScreen(TTF_Font *, SDL_Renderer *);

// Libère toutes les ressources
void FreeAll(Player *, Flechettes *, Canars *);

// Chargement des niveaux
void LoadLevel(Canars *, int);
void LevelOne(Canars *);
void LevelTwo(Canars *);
void LevelThree(Canars *);

// Collisions
bool CheckCollision(SDL_Rect *, SDL_Rect *);
void CollideProjectile(Flechettes *, Canars *, Player *, Walls *);
void CollideCanarPlayer(Player *, Canars *);

// Score
void UpdateScore(Player *);

// UI joueur
void RenderPlayerHeart(Player *,SDL_Renderer *, TTF_Font *);

// Pause
void Pause(SDL_Renderer *, TTF_Font *, Player *);

// Reset de l'etat du jeu
void ResetAll(Player *, Canars *, GameState *);

// Rendu général
void RenderAll(SDL_Renderer *, Player *, Flechettes *, Canars *, Walls *, TTF_Font *);
void RenderScore(Player *, TTF_Font *, SDL_Renderer *);

// Mouvements / logique
void MoveElements(Flechettes *, Canars *, Uint32 *, Uint32);
void CollideElements(Flechettes *, Canars *, Player *, Walls *);
void CreateWalls(Walls *);

// Render individuels
void RenderPlayer(Player *, SDL_Renderer *);
void RenderProjectiles(Flechettes *, SDL_Renderer *);
void RenderEnnemies(Canars *, SDL_Renderer *);
void RenderWalls(Walls *, SDL_Renderer *);

// Sauvegarde score
void SaveHighScore(int);

// Input clavier
void Input(const Uint8 *, Player *, Flechettes *);

#endif
