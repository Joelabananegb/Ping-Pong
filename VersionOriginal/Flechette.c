#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Flechette.h"
#include "Affichage.h"

ListeFlechette *ListeFlechetteInit(int hauteur, int lvl)
{
  ListeFlechette *liste = malloc(sizeof(ListeFlechette));
  liste->head = NULL;
  liste->lvl = lvl;
  return liste;
};

void FlechetteDesallouer(ListeFlechette **flechettes)
{
  Flechette *current = (*flechettes)->head;
  while(current != NULL)
  {
    Flechette *tmp = current;
    current = current->next;
    free(tmp);
  }

  free((*flechettes));
  (*flechettes) = NULL;
}

void AjouterFlechette(ListeFlechette *flechettes, int x, int y)
{
  Flechette *newFlechette = malloc(sizeof(Flechette));
  newFlechette->y = y;
  newFlechette->x = x;
  newFlechette->velocity = flechettes->lvl;
  newFlechette->next = flechettes->head;
  flechettes->head = newFlechette;
}

void AfficherFlechette(ListeFlechette *flechettes, Affichage *grille)
{
  Flechette *current = flechettes->head;

  while (current != NULL)
  {
    if (current->x >= 0 && current->x < grille->hauteur)
    {
      strcpy(grille->tab[current->x][current->y], "|");
    }

    current = current->next;
  }
}

void FlechetteAction(ListeFlechette *flechettes)
{
  Flechette *current = flechettes->head;
  Flechette *prev = NULL;

  while (current != NULL)
  {
    current->x -= current->velocity; // monte vers le haut

    if (current->x <= 0)
    {
      if (prev == NULL)
      {
        flechettes->head = current->next;
      }
      else
      {
        prev->next = current->next;
      }
      Flechette *tmp = current;
      current = current->next;
      free(tmp);
    }
    else
    {
      prev = current;
      current = current->next;
    }
  }
}
