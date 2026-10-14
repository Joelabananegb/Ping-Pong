#ifndef CANON_H
#define CANON_H

#include "Affichage.h"
#include "Flechette.h"

enum action_canon {Gauche_canon, Droite_canon, Tir};

typedef struct{
  int largeur, hauteur;   /* Taille du rectangle de la base du canon */
  int pos_min, pos_max;   /* Position min (à gauche) et max (à droite) */
  int xpos, ypos;         /* Case supérieure gauche de la position du Canon */ 
  int pas;                /* Nombre de cases de déplacement d'un Canon à chaque appui */
  int ypos_old;           /* Position précédente du Canon */ 
} Canon;

Canon *CanonInitialiser(int, int, int);
void CanonDesallouer(Canon **);
void CanonAction(Canon *, enum action_canon, ListeFlechette *);
void CanonAfficher(Canon *, Affichage* );

#endif 


