#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>
#include "./header/game.h" // Contient les éléments du jeu

int main()
{
  srand(time(NULL));

  // Init SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    SDL_Log("Erreur SDL_Init: %s", SDL_GetError());
    return 1;
  }

  // Init images
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
  {
    SDL_Log("Erreur IMG_Init: %s", IMG_GetError());
    SDL_Quit();
    return 1;
  }

  // Init texte
  if (TTF_Init() == -1)
  {
    SDL_Log("Erreur TTF_init: %s", TTF_GetError());
    SDL_Quit();
    return 1;
  }

  // Pointeurs principaux du jeu
  Player *player = NULL;
  Flechettes *flechettes = NULL;
  Canars *canars = NULL;
  Walls *walls = NULL;
  GameState *gameState = NULL;

  // Création fenêtre
  SDL_Window *window = SDL_CreateWindow("Earth invader", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  if (!window)
  {
    SDL_Log("Erreur fenêtre: %s", SDL_GetError());
    goto cleanup;
  }

  // Renderer
  SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!render)
  {
    SDL_Log("Erreur renderer: %s", SDL_GetError());
    goto cleanup;
  }

  // Background
  SDL_Texture *background = IMG_LoadTexture(render,"./assets/SpaceInvaders_Background.png");
  if (!background)
  {
    SDL_Log("Erreur background: %s", IMG_GetError());
    goto cleanup;
  }

  // Font
  TTF_Font *font = TTF_OpenFont("./assets/space_invaders.ttf",24);
  if (!font)
  {
    SDL_Log("Erreur font: %s", TTF_GetError());
    goto cleanup;
  }

  // Texture commune des sprites
  SDL_Texture *TextureGen = IMG_LoadTexture(render, "./assets/SpaceInvaders.png");

  // Init game
  gameState = InitGameState();
  player = InitPlayer(render, "./assets/SpaceInvaders.png","./assets/SpaceInvaders_Icons.png");
  flechettes = InitFlechettes(TextureGen);
  canars = InitCanar(TextureGen);
  walls = InitWalls(TextureGen);

  // Boucle principale
  while (gameState->running)
  {
    SDL_RenderClear(render);

    GameBackground(render, background);

    Game(render, player, flechettes, canars, walls, font, gameState);

    // Game over
    if(!player->alive)
    {
      SDL_RenderClear(render);
      GameOver(render, background, font, player);
      SDL_RenderPresent(render);
      SDL_Delay(2000);
      goto cleanup;
    }

    SDL_RenderPresent(render);
    SDL_Delay(16);
  }

cleanup:
  // Sauvegarde score avant de quit
  if (player && player->score > player->highScore) {
    player->highScore = player->score;
    SaveHighScore(player->highScore);
  }

  // Libération mémoire
  FreeAll(player, flechettes, canars);

  SDL_DestroyTexture(background);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
