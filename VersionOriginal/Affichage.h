#ifndef AFFICHAGE
#define AFFICHAGE

#include <stdlib.h>
#include <stdio.h>


/* Structure necessaire aux fonctions d affichage*/
typedef struct{  
  int largeur, hauteur;     /* Largeur, Hauteur de l'affichage */
  char *** tab; /* Tableau à deux dimensions de chaînes de caractères ASCII */
} Affichage;


Affichage *AffichageInitialiser(int, int);   /* Alloue et initialise */
void AffichageDesallouer(Affichage **);           
void AffichageCadre(Affichage *);                /* Place un cadre autour de l'Affichage */
void AffichageVider(Affichage *);                /* Remplit l'Affichage de case noire */
void AffichageDessiner(Affichage *);             /* Affiche le tableau à l'écran */

#endif
