#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

// Nombre maximum de tirs du joueur
#define MAX_AMMO 3

// Types de projectiles
typedef enum {
  PLAYERBULLET,
  ENEMYBULLET
} bulletType;

// Structure d'une fléchette
typedef struct Flechette
{
  short velocity;         // Vitesse du projectile

  SDL_Rect rect;          // Sprite source
  SDL_Rect destRect;      // Position et taille à l'écran

  SDL_Texture *texture;   // Texture utilisée

  bulletType type;        // Type de projectile joueur ou ennemie

  struct Flechette *next; // Projectile suivant
} Flechette;

// Liste des projectiles
typedef struct
{
  Flechette *head;        // Premier projectile
  int ammo;               // Nombre de tirs actifs
  SDL_Texture *textureGen; // Texture partagée
} Flechettes;

// Initialise les projectiles
Flechettes *InitFlechettes(SDL_Texture *);

// Libère les projectiles
void FreeFlechettes(Flechettes **);

// Ajoute un projectile
void AddFlechette(Flechettes *, int, int, int, bulletType);

// Déplace les projectiles
void MoveFlechettes(Flechettes *);

#endif
