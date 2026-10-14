#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Canon.h"


Canon *CanonInitialiser(int posMin, int posMax, int hauteurGrille)
{
   Canon *canon = malloc(sizeof(Canon));
   canon->hauteur = 2;
   canon->largeur = 11;
   canon->xpos = hauteurGrille-canon->hauteur - 1;
   canon->ypos = (posMin + posMax - canon->largeur) / 2; 
   canon->ypos_old = canon->xpos; 
   canon->pos_min = posMin + 3; 
   canon->pos_max = posMax - 3;
   canon->pas = 1;
   return canon;
}

void CanonDesallouer(Canon** canon)
{
  free(*canon);
  *canon = NULL;
}


void CanonAction(Canon *canon, enum action_canon actC, ListeFlechette *Flechettes)
{
  canon->ypos_old = canon->ypos; 

  switch (actC)
  {
    case Gauche_canon:
      canon->ypos -= canon->pas;
      break;
    case Droite_canon:
      canon->ypos += canon->pas;
      break;  
    case Tir:
      // Lance une fléchette
      AjouterFlechette(Flechettes, canon->xpos - 3,canon->ypos + canon->largeur / 2);
      break;       
  }

  if ((canon->ypos < canon->pos_min) || (canon->ypos > canon->pos_max - canon->largeur)) // verifier que le canon ne sort pas du cadre de jeu
  {
   canon->ypos = canon->ypos_old;
  }
}

void CanonAfficher(Canon *canon, Affichage* grille)
{ 
  for (int x = canon->xpos; x < canon->xpos + canon->hauteur; x++)
  {
    for (int y = canon->ypos; y < canon->ypos + canon->largeur; y++)
    {
      if (x >= 0 && x < grille->hauteur && y>=0 && y < grille->largeur)
      {
        strcpy(grille->tab[x][y], "♖");//"\33[44m ");
      }
    }

    strcpy(grille->tab[canon->xpos-1][canon->ypos + canon->largeur / 2-1], "♖");//"\33[44m ");
    strcpy(grille->tab[canon->xpos-1][canon->ypos + canon->largeur / 2], "♖");//"\33[44m ");
    strcpy(grille->tab[canon->xpos-1][canon->ypos + canon->largeur / 2+1], "♖");//"\33[44m ");
    strcpy(grille->tab[canon->xpos-2][canon->ypos + canon->largeur / 2-1], "♖");//"\33[44m ");
    strcpy(grille->tab[canon->xpos-2][canon->ypos + canon->largeur / 2], "♖");//"\33[44m ");
    strcpy(grille->tab[canon->xpos-2][canon->ypos + canon->largeur / 2+1], "♖");//"\33[44m ");
  }
}
