#include "game.h"
/****************************************
 *                                      *
 *    TODO Score show                   *
 *    TODO Ball movement collision wall *
 *    TODO Ball and racket collision    *
 *    TODO Scoring                      *
 *    TODO Game over                    *
 *                                      *
 ****************************************/

SDL_Rect rect_left  = {RACKET_PADDING + 10, (SCREEN_HEIGHT / 2) - BALL_SIZE*2, RACKET_PADDING, BALL_SIZE*3};
SDL_Rect rect_right = {SCREEN_WIDTH - RACKET_PADDING - 20, (SCREEN_HEIGHT / 2) - BALL_SIZE*2, RACKET_PADDING, BALL_SIZE*3};
SDL_Rect rect_ball  = {(SCREEN_WIDTH - BALL_SIZE) / 2, (SCREEN_HEIGHT - BALL_SIZE) / 2, BALL_SIZE, BALL_SIZE};
SDL_Rect rect_mid   = {SCREEN_WIDTH/2, 0, 5, LINE_HEIGHT};

void Log(const char *log)
{
  SDL_Log("Erreur: %s", log);
}

void Draw(SDL_Renderer *render)
{
  SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

  SDL_RenderFillRect(render, &rect_ball);
  SDL_RenderFillRect(render, &rect_left);
  SDL_RenderFillRect(render, &rect_right);

  for (int i =0; i<= COUNT_LINE; i++) {
    if (i%2 == 0){
      rect_mid.y = i*LINE_HEIGHT;
      SDL_RenderFillRect(render, &rect_mid);
    }
  }

}
void MoveBall(double dt)
{
  int new_pos_x = SPEED * dt;
  if (rect_ball.x + new_pos_x <= 0 || rect_ball.x + new_pos_x >= SCREEN_HEIGHT){
    rect_ball.x += -(SPEED *dt);
  }

  if (rect_ball.y + new_pos_x <= 0 || rect_ball.y + new_pos_x >= SCREEN_WIDTH){
    rect_ball.y += -(SPEED *dt);
  }
}

void Game(SDL_Renderer *render)
{
  int running = 1;
  while(running){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT){
        running = 0;
      }
    }

    SDL_SetRenderDrawColor(render, 19,19,24,255);
    SDL_RenderClear(render);
    Draw(render);
    MoveBall(0.2);
    SDL_RenderPresent(render);
  }
}
