#ifndef ENNEMIE_H
#define ENNEMIE_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projectile.h"

// Structure d'un ennemi
typedef struct Canar
{
  SDL_Rect rect;         // Sprite source
  SDL_Rect destRect;     // Position et taille à l'écran
  SDL_Texture *texture;  // Texture du canard

  short velocity;        // Vitesse de déplacement
  struct Canar *next;    // Canard suivant
} Canar;

// Liste chaînée des ennemis
typedef struct
{
  Canar *head;           // Premier canard
  int numberOfCanar;     // Nombre total de canards
  int numberInit;        // Nombre initial
  SDL_Texture *textureGen; // Texture partagée
} Canars;

// Directions possibles
enum Moves 
{
  LEFT = -1,
  RIGTH = 1
};

// Initialise la liste des canards
Canars *InitCanar(SDL_Texture *);

// Retourne un canard aléatoire
Canar *GetRandomCanar(Canars *);

// Met à jour les canards
void UpdateAll(Canars *);

// Libère la mémoire
void FreeCanar(Canars **);

// Ajoute un canard
void AddCanar(Canars *, int, int);

// Déplace les canards
void MoveCanar(Canars *);

// Fait tirer un canard
void Attack(Canars *, Flechettes *);
#endif
