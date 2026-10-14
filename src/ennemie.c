#include "./header/ennemie.h"

// Direction actuelle des ennemis
enum Moves direction = RIGTH;

// Initialise la structure des canards
Canars *InitCanar(SDL_Texture *texture)
{
  Canars *canars = malloc(sizeof(Canars));
  canars->head = NULL;
  canars->numberOfCanar = 0;
  canars->numberInit = 0;
  canars->textureGen = texture;
  return canars;
}

// Libère tous les canards
void FreeCanar(Canars **canars)
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

// Ajoute un canard à la liste
void AddCanar(Canars *canars, int x, int y)
{
  Canar *newCanar = malloc(sizeof(Canar));

  // Sprite source
  newCanar->rect = (SDL_Rect){0,0, 16, 16};

  // Position et taille à l'écran
  newCanar->destRect = (SDL_Rect){x,y,64,64};

  newCanar->texture = canars->textureGen;
  newCanar->velocity = 16;

  // Ajout en tête de liste
  newCanar->next = canars->head;
  canars->head = newCanar;

  canars->numberOfCanar++;
}

// Déplace tous les canards vers le bas
void UpdateAll(Canars *canars)
{
  Canar *current = canars->head;

  while(current!=NULL){
    current->destRect.y += 10;
    current = current->next;
  }
}

// Déplacement horizontal des canards
void MoveCanar(Canars *canars)
{
  Canar *current = canars->head;

  while (current != NULL)
  {
    current->destRect.x += current->velocity * direction;
    current = current->next;
  }

  bool hitEdge = false;

  current = canars->head;

  // Vérifie si un bord est touché
  while (current != NULL)
  {
    if (current->destRect.x <= 0 || current->destRect.x >= 700)
    {
      hitEdge = true;
      break;
    }

    current = current->next;
  }

  // Change de direction et descend
  if (hitEdge)
  {
    direction *= -1;

    current = canars->head;

    while (current != NULL)
    {
      current->destRect.y += 16;
      current = current->next;
    }
  }
}

// Retourne un canard aléatoire
Canar *GetRandomCanar(Canars *canars)
{
  if (canars->head == NULL) return NULL;

  int target = rand() % canars->numberOfCanar;

  Canar *current = canars->head;

  for (int i = 0; i < target; i++)
  {
    current = current->next;
  }

  return current;
}

// Fait tirer un canard aléatoire
void Attack(Canars *canars, Flechettes *flechettes)
{
    Canar *shooter = GetRandomCanar(canars);

    if (shooter == NULL) return;

    AddFlechette(flechettes, shooter->destRect.x + shooter->destRect.w / 2 - 8, shooter->destRect.y + shooter->destRect.h + 10, 8, ENEMYBULLET);
}
