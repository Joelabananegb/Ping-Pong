#include "./header/wall.h"

// Initialise la liste des murs
Walls *InitWalls(SDL_Texture *texture)
{
  Walls *walls = malloc(sizeof(Walls));

  walls->textureGen = texture;
  walls->head = NULL;

  return walls;
}

// Crée un nouveau mur
void CreatWall(Walls *walls, int x)
{
  Wall *newWall = malloc(sizeof(Wall));

  // Sprite source
  newWall->rect = (SDL_Rect){50,16,27,16};

  // Position et taille à l'écran
  newWall->destRect = (SDL_Rect){x * 90, (600 / 2) + 70, 80, 80};

  newWall->texture = walls->textureGen;

  // Points de vie du mur
  newWall->health = 5;

  // Ajout en tête de liste
  newWall->next = walls->head;
  walls->head = newWall;
}

// Supprime tous les murs
void ResetWalls(Walls *walls)
{
  Wall *current = walls->head;

  while (current != NULL)
  {
    Wall *tmp = current;
    current = current->next;

    free(tmp);
  }

  walls->head = NULL;
}
