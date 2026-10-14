#ifndef FLECHETTE_H
#define FLECHETTE_H

#define MAX_FLECHETTE 20

#include "Affichage.h"

typedef struct Flechette {
  int x,y;
  int velocity;
  struct Flechette *next;
} Flechette;

typedef struct{
  Flechette *head;
  int lvl;
  int y_depart;
  int y_max;
  int nb;
  int nb_max;
} ListeFlechette;

ListeFlechette *ListeFlechetteInit(int, int);
void FlechetteDesallouer(ListeFlechette **);
void AjouterFlechette(ListeFlechette *, int, int);
void AfficherFlechette(ListeFlechette *, Affichage *);
void FlechetteAction(ListeFlechette *);

#endif
