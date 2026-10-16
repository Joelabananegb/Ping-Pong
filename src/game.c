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

int dx = 1;
int dy = -1;

void Log(const char *log)
{
  SDL_Log("Erreur: %s", log);
}

void Draw(SDL_Renderer *render,SDL_Rect rect_left,SDL_Rect rect_right,SDL_Rect rect_ball,SDL_Rect rect_mid,int h)
{
  SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

  SDL_RenderFillRect(render, &rect_ball);
  SDL_RenderFillRect(render, &rect_left);
  SDL_RenderFillRect(render, &rect_right);

  int lines = ((h / 100)*(h/ 100))+2;

  for (int i =0; i<= lines; i++) {
    if (i%2 == 0){
      rect_mid.y = i*LINE_HEIGHT;
      SDL_RenderFillRect(render, &rect_mid);
    }
  }

}

void MoveBall(double deltatime,SDL_Rect *rect_ball, int w, int h)
{
  double new_pos_x = dx*SPEED*deltatime + rect_ball->x;
  double new_pos_y = dy*SPEED*deltatime + rect_ball->y;
  printf("new_pos_x = %d\n",(int)new_pos_x);
  printf("new_pos_xy= %d\n",(int)new_pos_y);

  if (new_pos_x > 0 && new_pos_x < SCREEN_HEIGHT){
    dx = -dx;
  }else{
    rect_ball->x = (int)new_pos_x;
  }

  if (new_pos_y > 0 && new_pos_y < SCREEN_HEIGHT){
    dy = -dy;
  }else{
    rect_ball->y = (int)new_pos_y;
  }
}

void Game(SDL_Renderer *render, SDL_Window *window)
{
  int width, height;
  SDL_GetWindowSize(window, &width, &height);

  SDL_Rect rect_left  = {RACKET_PADDING + 10, (height/ 2) - BALL_SIZE*2, RACKET_PADDING, BALL_SIZE*3};
  SDL_Rect rect_right = {SCREEN_WIDTH - 30, (height/ 2) - BALL_SIZE*2, RACKET_PADDING, BALL_SIZE*3};
  SDL_Rect rect_ball  = {(width - BALL_SIZE) / 2, (height- BALL_SIZE) / 2, BALL_SIZE, BALL_SIZE};
  SDL_Rect rect_mid   = {(width-5)/2, 0, 5, LINE_HEIGHT};

  int running = 1;
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 last = 0;
  double deltatime = 0;
  while(running){
    last = now;
    now = SDL_GetPerformanceCounter();
    deltatime = (double)(now-last)*1000/(double)SDL_GetPerformanceFrequency();
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
              width = event.window.data1;
              height = event.window.data2;

              rect_left.x  = RACKET_PADDING + 10;
              rect_left.y  = (height/ 2) - BALL_SIZE*2;
              rect_left.w  = RACKET_PADDING;
              rect_left.h  = BALL_SIZE*3;

              rect_right.x  = width - 30;
              rect_right.y  = (height/ 2) - BALL_SIZE*2;
              rect_right.w  = RACKET_PADDING;
              rect_right.h  = BALL_SIZE*3;

              rect_ball.x  = (width - BALL_SIZE) / 2;
              rect_ball.y  = (height- BALL_SIZE) / 2;
              rect_ball.w  = BALL_SIZE;
              rect_ball.h  = BALL_SIZE;             

              rect_mid.x  = (width - 5) / 2;
              rect_mid.y  = 0;
              rect_mid.w  = 5;
              rect_mid.h  = LINE_HEIGHT;

      }

      if (event.type == SDL_QUIT){
        running = 0;
      }
    }

    if (keystate[SDL_SCANCODE_UP] && rect_left.y > 0){
      rect_left.y -= SPEED *deltatime;
    }

    if (keystate[SDL_SCANCODE_DOWN] && rect_left.y < height - BALL_SIZE*3){
      rect_left.y += SPEED * deltatime;
    }

    if (keystate[SDL_SCANCODE_E] && rect_right.y > 0){
      rect_right.y -= SPEED * deltatime;
    }

    if (keystate[SDL_SCANCODE_D] && rect_right.y < height - BALL_SIZE*3){
      rect_right.y += SPEED * deltatime;
    }

    SDL_SetRenderDrawColor(render, 19,19,24,255);
    SDL_RenderClear(render);
    Draw(render, rect_left, rect_right, rect_ball, rect_mid, height);
    MoveBall(deltatime, &rect_ball, width,height);
    SDL_RenderPresent(render);
  }
}
