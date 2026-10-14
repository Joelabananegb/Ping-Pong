#include "./header/projectile.h"

// Initialise la liste des projectiles
Flechettes *InitFlechettes(SDL_Texture *texture)
{
  Flechettes *projectiles = malloc(sizeof(Flechettes));

  projectiles->head = NULL;
  projectiles->ammo = 0;
  projectiles->textureGen = texture;

  return projectiles;
}

// Libère tous les projectiles
void FreeFlechettes(Flechettes **flechettes)
{
  Flechette *current = (*flechettes)->head;

  while (current != NULL)
  {
    Flechette *tmp = current;
    current = current->next;

    free(tmp);
  }

  free((*flechettes));
  (*flechettes) = NULL;
}

// Ajoute un projectile
void AddFlechette(Flechettes *flechettes, int x, int y, int velo, bulletType type)
{
  // Vérifie la limite de munitions
  if (flechettes->ammo < MAX_AMMO)
  {
    Flechette *newFlechette = malloc(sizeof(Flechette));

    // Sprite source
    newFlechette->rect = (SDL_Rect){32, 0, 16, 16};

    // Position et taille à l'écran
    newFlechette->destRect = (SDL_Rect){x,y,64,64};

    newFlechette->texture = flechettes->textureGen;

    // Vitesse du projectile
    newFlechette->velocity = velo;

    // Type du projectile
    newFlechette->type = type;

    // Ajout en tête de liste
    newFlechette->next = flechettes->head;
    flechettes->head = newFlechette;

    flechettes->ammo++;
  }
}

// Déplace les projectiles
void MoveFlechettes(Flechettes *flechettes)
{
  Flechette *current = flechettes->head;
  Flechette *prev = NULL;

  while (current != NULL)
  {
    // Déplacement vertical
    current->destRect.y += current->velocity;

    // Supprime le projectile hors écran
    if (current->destRect.y <= -64 || current->destRect.y >= 600)
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

      flechettes->ammo--;

      free(tmp);
    }
    else
    {
      prev = current;
      current = current->next;
    }
  }
}
