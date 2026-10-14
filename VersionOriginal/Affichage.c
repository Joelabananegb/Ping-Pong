#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Affichage.h"

/* Alloue et initialise une grille */
Affichage *AffichageInitialiser(int largeur, int hauteur)
{
  Affichage *grille;
  grille = malloc(sizeof(Affichage));
  grille->largeur = largeur; 
  grille->hauteur = hauteur;
  grille->tab = malloc(hauteur * sizeof(char **));

  for (int x = 0; x < hauteur; x++)
  {
    grille->tab[x] = malloc(largeur * sizeof(char *));
    for (int y = 0; y < largeur; y++)
    {
       grille->tab[x][y]=malloc(7 * sizeof(char)); // Une case peut faire 6 caractères ASCII pour les séquences d'échappement
    }
  }
  return grille;
}

/* Desallocation de la grille */
void AffichageDesallouer(Affichage **grille)
{
  for (int x = 0; x < (*grille)->hauteur; x++)
  {
    for (int y = 0; y < (*grille)->largeur; y++)
    {
       free((*grille)->tab[x][y]);    
    }
    free((*grille)->tab[x]);
  }
  free((*grille)->tab);
  free(*grille);
  *grille = NULL;
}


/* Remplit une grille de vide */
void AffichageVider(Affichage *grille)
{
  for (int x = 0; x < grille->hauteur; x++)
  {
    for (int y = 0; y < grille->largeur; y++)
    {
       strcpy(grille->tab[x][y], " "); /* met une case vide */
    }
  }
}

void AffichageCadre(Affichage *grille)
{
   
  /* Cadre */
  for (int x = 0; x < grille->hauteur; x++)
  {
      strcpy(grille->tab[x][0], "\33[42m ");
      strcpy(grille->tab[x][grille->largeur-1], "\33[42m ");
  }

  for (int y = 0; y < grille->largeur; y++)
  {
      strcpy(grille->tab[0][y], "\33[42m ");
      strcpy(grille->tab[grille->hauteur-1][y], "\33[42m ");
  }
}


/* Affiche une grille dans le terminal */
void AffichageDessiner(Affichage *grille)
{
  printf("\33[2J"); /* Efface tout l'ecran */
  printf("\33[H");  /* Deplace le curseur en position (0,0) */ 
  
  for (int x = 0; x < grille->hauteur; x++)
  {
    for (int y = 0; y < grille->largeur; y++)
    {  
      printf("%s\033[00m", grille->tab[x][y]); /* Affiche les cases de la grille */ 
    }
    printf("\33[1E");     /* Retour à la ligne */
  }

  printf("\033[00m"); /* Declare le fond noir pour la suite */
  printf("\33[1E");
}
