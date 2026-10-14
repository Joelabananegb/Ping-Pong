#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Canar.h"

ListeCanar *ListeCanarInit(int lvl)
{
  ListeCanar *liste = malloc(sizeof(ListeCanar));
  liste->lvl = lvl;
  liste->head = NULL;
  return liste;
}

void CanarDesallouer(ListeCanar **canars)
{
  Canar *current = (*canars)->head;

  while(current != NULL)
  {
    Canar *tmp = current;
    current = current->next;
    free(tmp);
  }
  
  free((*canars));
  (*canars) = NULL;
}

void AjouterCanar(ListeCanar *canars, int x, int y)
{
  Canar *newCanar = malloc(sizeof(Canar));
  newCanar->y = y;
  newCanar->x = x;
  newCanar->alive = true;
  newCanar->velocity = canars->lvl;
  newCanar->next = canars->head;
  canars->head = newCanar;
}

void AfficherCanar(ListeCanar *canars, Affichage *grille)
{
  Canar *current = canars->head;

  while (current != NULL)
  {
    if (current->alive)
    {
      if (current->x >= 0 && current->x < grille->hauteur &&
          current->y >= 0 && current->y < grille->largeur)
      {
        strcpy(grille->tab[current->x][current->y], "C");
      }
    }

    current = current->next;
  }
}

void CanarAction(ListeCanar *canars)
{
  Canar *current = canars->head;
  Canar *prev = NULL;

  while (current != NULL)
  {
    current->x += current->velocity;

    // suppression si hors écran
    if (current->x <= 0)
    {
      Canar *tmp = current;

      if (prev == NULL)
      {
        canars->head = current->next;
        current = canars->head;
      }
      else
      {
        prev->next = current->next;
        current = current->next;
      }

      free(tmp);
    }
    else
    {
      prev = current;
      current = current->next;
    }
  }
}
