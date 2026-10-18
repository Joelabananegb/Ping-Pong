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


int running = 1;

GameStruct *Init(SDL_Window *window, SDL_Renderer *render)
{
  GameStruct *game = malloc(sizeof(GameStruct));
  game->left    = {RACKET_PADDING + 10, (SCREEN_HEIGHT/ 2) - BALL_SIZE*2, RACKET_PADDING, BALL_SIZE*6};
  game->right   = {SCREEN_WIDTH - 30, (SCREEN_HEIGHT/ 2) - BALL_SIZE*2, RACKET_PADDING, BALL_SIZE*6};
  game->ball    = {(SCREEN_WIDTH - BALL_SIZE) / 2, (SCREEN_HEIGHT- BALL_SIZE) / 2, BALL_SIZE, BALL_SIZE};
  game->dots    = {(SCREEN_WIDTH - 5)/2, 0, 5, LINE_HEIGHT};
  game->ball_x  = 100.0;
  game->ball_y  = 100.0;

  game->dx = 1;
  game->dy = -1;

  game->window = window;
  game->render = render;
  return game;
}

void Update(GameStruct *gameStruct){
  int width, height;
  SDL_GetWindowSize(gameStruct->window, &width, &height);

  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
      gameStruct->w = event.window.data1;
      gameStruct->h = event.window.data2;

      gameStruct->left.x  = RACKET_PADDING + 10;
      gameStruct->left.y  = (gameStruct->h/ 2) - BALL_SIZE*2;
      gameStruct->left.w  = RACKET_PADDING;
      gameStruct->left.h  = BALL_SIZE*6;

      gameStruct->right.x  = gameStruct->w- 30;
      gameStruct->right.y  = (gameStruct->h/ 2) - BALL_SIZE*2;
      gameStruct->right.w  = RACKET_PADDING;
      gameStruct->right.h  = BALL_SIZE*6;

      gameStruct->ball.x  = (gameStruct->w- BALL_SIZE) / 2;
      gameStruct->ball.y  = (gameStruct->h- BALL_SIZE) / 2;
      gameStruct->ball.w  = BALL_SIZE;
      gameStruct->ball.h  = BALL_SIZE;

      gameStruct->dots.x  = (gameStruct->w - 5) / 2;
      gameStruct->dots.y  = 0;
      gameStruct->dots.w  = 5;
      gameStruct->dots.h  = LINE_HEIGHT;
    }

    if (event.type == SDL_QUIT){
      running = 0;
    }
  }

  if (keystate[SDL_SCANCODE_UP]){
    int rect_left_ny = rect_left.y + SPEED * deltatime;
    if (rect_left_ny + BALL_SIZE*6 < height){
      rect_left.y -= rect_left.y + SPEED * deltatime;
    }
  }

  /*if (keystate[SDL_SCANCODE_DOWN] && rect_left.y < height - BALL_SIZE*3){
    rect_left.y += SPEED * deltatime;
  }

  if (keystate[SDL_SCANCODE_E] && rect_right.y > 0){
    rect_right.y -= SPEED * deltatime;
  }

  if (keystate[SDL_SCANCODE_D] && rect_right.y < height - BALL_SIZE*3){
    rect_right.y += SPEED * deltatime;
  }*/

}

void Log(const char *log)
{
  SDL_Log("Erreur: %s", log);
}

/*void Draw(SDL_Renderer *render, int height)
{
  int lines = ((height / 100)*(height/ 100))+2;

  SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

  SDL_RenderFillRect(render, &rect_ball);
  SDL_RenderFillRect(render, &rect_left);
  SDL_RenderFillRect(render, &rect_right);


  for (int i = 0; i <= lines; i++) {
    if (i%2 == 0){
      rect_mid.y = i*LINE_HEIGHT;
      SDL_RenderFillRect(render, &rect_mid);
    }
  }
}

void MoveBall(double deltatime, int width, int height)
{
    ball_x += dx * SPEED * deltatime;
    ball_y += dy * SPEED * deltatime;

    if (ball_x < 0) {
        ball_x = 0;
        dx = -dx;
    } else if (ball_x > width - rect_ball->w) {
        ball_x = width - rect_ball->w;
        dx = -dx;
    }

    if (ball_y < 0) {
        ball_y = 0;
        dy = -dy;

    } else if (ball_y > height - rect_ball->h) {
        ball_y = height - rect_ball->h;
        dy = -dy;
    }

    rect_ball->x = (int)lround(ball_x);
    rect_ball->y = (int)lround(ball_y);
}*/

void Game(SDL_Renderer *render, SDL_Window *window)
{

  GameStruct *gameStruct = Init(render, window);

  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 last = 0;
  double deltatime = 0;

  while(running){
    last = now;
    now = SDL_GetPerformanceCounter();
    deltatime = (double)(now-last)*1000/(double)SDL_GetPerformanceFrequency();

    SDL_SetRenderDrawColor(render, 19, 19, 24, 255);
    SDL_RenderClear(render);
    Draw(gameStruct);
    MoveBall(deltatime);
    SDL_RenderPresent(render);
  }
}
