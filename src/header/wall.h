#ifndef WALL_H
#define WALL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

// Structure d'un mur
typedef struct Wall {
  SDL_Rect rect;          // Sprite source
  SDL_Rect destRect;      // Position et taille à l'écran
  SDL_Texture *texture;   // Texture du mur

  int health;             // Points de vie

  struct Wall *next;      // Mur suivant
} Wall;

// Liste des murs
typedef struct walls {
  Wall *head;             // Premier mur
  SDL_Texture *textureGen; // Texture partagée
} Walls;

// Initialise les murs
Walls *InitWalls(SDL_Texture *);

// Crée un mur
void CreatWall(Walls *, int);

// Réinitialise les murs
void ResetWalls(Walls *);

#endif
