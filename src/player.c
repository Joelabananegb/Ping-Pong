#include "./header/player.h"

// Charge le meilleur score depuis le fichier
int LoadHighScore() {
  FILE *file = fopen("bestScore.txt", "r");

  int score = 0;

  if (file)
  {
    unsigned int encrypted;

    // Lit le score chiffré
    if (fscanf(file, "%X", &encrypted) == 1)
    {
      // Déchiffrement simple avec XOR
      score = encrypted ^ 0xDEADBEEF;
    }

    fclose(file);
  }

  return score;
}

// Initialise le joueur
Player *InitPlayer(SDL_Renderer *render, const char *imgpath, const char *imgpathHearth)
{
  Player *player = malloc(sizeof(Player));

  if (!player) return NULL;

  // Sprite source
  player->rect = (SDL_Rect){64, 0, 16, 16};

  // Position et taille à l'écran
  player->destRect = (SDL_Rect){SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 + 180, 64, 64};

  // Chargement des textures
  player->texture = IMG_LoadTexture(render, imgpath);
  player->heartTexture = IMG_LoadTexture(render, imgpathHearth);

  // Stats du joueur
  player->velocity = 8;
  player->attack = 10;
  player->health = 100;
  player->maxHealth = 100;

  // Scores
  player->score = 0;
  player->highScore = LoadHighScore();

  // État du joueur
  player->alive = true;

  // Sprite du coeur
  player->heartRect = (SDL_Rect){80,96,16,16};
  player->heartDestRect = (SDL_Rect){10,10,64,64};

  return player;
}

// Réinitialise les stats du joueur
void ResetPlayer(Player *player)
{
  player->destRect = (SDL_Rect){SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 + 180, 64, 64};

  player->health = 100;
  player->score = 0;
  player->alive = true;
}

// Déplacement à gauche
void MoveLeft(Player *player)
{
  if (player->destRect.x >= 0)
  {
    player->destRect.x -= player->velocity;
  }
}

// Déplacement à droite
void MoveRight(Player *player)
{
  if (player->destRect.x <= SCREEN_WIDTH - 80)
  {
    player->destRect.x += player->velocity;
  }
}

// Déplacement vers le haut
void MoveUp(Player *player)
{
  if (player->destRect.y >= 0)
  {
    player->destRect.y -= player->velocity;
  }
}

// Déplacement vers le bas
void MoveDown(Player *player)
{
  if (player->destRect.y <= SCREEN_HEIGHT - 80)
  {
    player->destRect.y += player->velocity;
  }
}

// Libère la mémoire du joueur
void FreePlayer(Player **player)
{
  if (!player || !(*player)) return;

  // Supprime les textures
  if ((*player)->texture) SDL_DestroyTexture((*player)->texture);

  if ((*player)->heartTexture) SDL_DestroyTexture((*player)->heartTexture);

  free(*player);
  *player = NULL;
}

// Inflige des dégâts au joueur
void PlayerDamage(Player *player)
{
  // Vérifie si le joueur est mort
  if (player->alive && player->health <= 0)
  {
    player->alive = false;
  }
  else
  {
    // Retire de la vie
    player->health -= 25;
  }
}
