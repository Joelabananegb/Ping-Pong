#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH    700
#define SCREEN_HEIGHT   500
#define BALL_SIZE       20
#define RACKET_PADDING  10
#define COUNT_LINE      24
#define LINE_HEIGHT     20
#define SPEED           5

void Log(const char *);
void Draw(SDL_Renderer *);
void Game(SDL_Renderer *);

#endif // !GAME_H
