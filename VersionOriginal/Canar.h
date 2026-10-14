#ifndef CANAR_H
#define CANAR_H

#include "Affichage.h"
#include <stdbool.h>

typedef struct Canar {
  int x, y;
  int velocity;
  bool alive;
  struct Canar *next;
} Canar;

typedef struct {
  Canar *head;
  int lvl;
}ListeCanar;

ListeCanar *ListeCanarInit(int);
void CanarDesallouer(ListeCanar **);
void AjouterCanar(ListeCanar *, int, int);
void AfficherCanar(ListeCanar *, Affichage *);
void CanarAction(ListeCanar *);
#endif 
