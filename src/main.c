#include "game.h"

int main()
{
  if (SDL_Init(SDL_INIT_EVERYTHING)){
    Log(SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Pong game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  if (window==NULL){
    Log(SDL_GetError());
    return 1;
  }

  SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (render==NULL){
    Log(SDL_GetError());
    return 0;
  }

  Game(render);

  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
