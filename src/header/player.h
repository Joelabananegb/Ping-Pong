#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Structure du joueur
typedef struct{

  short velocity;          // Vitesse de déplacement

  int health, maxHealth;   // Vie actuelle et max
  int score, highScore;    // Score actuel et meilleur score
  int attack;              // Dégâts

  SDL_Rect rect;           // Sprite source
  SDL_Rect destRect;       // Position et taille à l'écran

  SDL_Texture *texture;    // Texture du joueur

  SDL_Texture *heartTexture; // Texture des coeurs
  SDL_Rect heartRect;        
  SDL_Rect heartDestRect;

  bool alive;              // État du joueur

} Player;

// Charge le meilleur score
int LoadHighScore();

// Initialise le joueur
Player *InitPlayer(SDL_Renderer *, const char *, const char *);

// Réinitialise le joueur
void ResetPlayer(Player *player);

// Déplacements
void MoveLeft(Player *);
void MoveRight(Player *);
void MoveUp(Player *);
void MoveDown(Player *);

// Inflige des dégâts au joueur
void PlayerDamage(Player *);

// Libère la mémoire du joueur
void FreePlayer(Player **);

#endif
