#include "game.h"

int main()
{
  if (SDL_Init(SDL_INIT_EVERYTHING)){
    Log(SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Pong game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

  if (window==NULL){
    Log(SDL_GetError());
    return 1;
  }

  SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (render==NULL){
    Log(SDL_GetError());
    return 1;
  }

  if (TTF_Init() == -1){
    Log(SDL_GetError());
    return 1;
  }

  TTF_Font *font = TTF_OpenFont("./fonts/BigBlueTerm437NerdFont-Regular.ttf", 40);
  if (!font){
    Log(SDL_GetError());
    return 1;
  }

  Game(render,window, font);

  TTF_CloseFont(font);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
