#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH    700
#define SCREEN_HEIGHT   500
#define BALL_SIZE       20
#define RACKET_PADDING  10
#define COUNT_LINE      24
#define LINE_HEIGHT     20
#define SPEED           3

typedef struct GameStruct{

  int             dx;
  int             dy;
  int             w;
  int             h;
  int             right_dy;
  int             left_dy;
  double          deltatime;
  double          ball_x;
  double          ball_y;


  SDL_Rect        left;
  SDL_Rect        right;
  SDL_Rect        ball;
  SDL_Rect        dots;
  SDL_Renderer    *render;
  SDL_Window      *window;

}GameStruct;

void Log(const char *);
GameStruct*Init(SDL_Window *, SDL_Renderer *);
void Update(GameStruct *);
void Draw(GameStruct *);
void MoveBall(GameStruct*);
void Game(SDL_Renderer *, SDL_Window *);

#endif // !GAME_H
