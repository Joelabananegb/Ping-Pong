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
void MoveBall(double dt,SDL_Rect rect_ball)
{
  int new_pos_x = rect_ball.w + (SPEED * dt);

  printf("%d\n",new_pos_x);
  if (rect_ball.x + new_pos_x > 0 && rect_ball.x + new_pos_x < SCREEN_HEIGHT){
    printf("hhelo\n");
    rect_ball.x += SPEED *dt;
  }

}

void Game(SDL_Renderer *render, SDL_Window *window)
{
  int width, height;
  SDL_GetWindowSize(window, &width, &height);

  SDL_Rect rect_left  = {RACKET_PADDING + 10, (height/ 2) - BALL_SIZE*2, RACKET_PADDING, BALL_SIZE*3};
  SDL_Rect rect_right = {SCREEN_WIDTH - 20, (height/ 2) - BALL_SIZE*2, RACKET_PADDING, BALL_SIZE*3};
  SDL_Rect rect_ball  = {(width - BALL_SIZE) / 2, (height- BALL_SIZE) / 2, BALL_SIZE, BALL_SIZE};
  SDL_Rect rect_mid   = {(width-5)/2, 0, 5, LINE_HEIGHT};

  double dt = 0.2;
  int running = 1;
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  while(running){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if (event.type == SDL_WINDOWEVENT &&
              event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
              width = event.window.data1;
              height = event.window.data2;

              rect_left.x  = RACKET_PADDING + 10;
              rect_left.y  = (height/ 2) - BALL_SIZE*2;
              rect_left.w  = RACKET_PADDING;
              rect_left.h  = BALL_SIZE*3;

              rect_right.x  = width - 20;
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
      rect_left.y -= SPEED*dt;
    }

    if (keystate[SDL_SCANCODE_DOWN] && rect_left.y < height - BALL_SIZE*3){
      rect_left.y += SPEED*dt;
    }

    if (keystate[SDL_SCANCODE_E] && rect_right.y > 0){
      rect_right.y -= SPEED*dt;
    }

    if (keystate[SDL_SCANCODE_D] && rect_right.y < height - BALL_SIZE*3){
      rect_right.y += SPEED*dt;
    }

    SDL_SetRenderDrawColor(render, 19,19,24,255);
    SDL_RenderClear(render);
    Draw(render, rect_left, rect_right, rect_ball, rect_mid, height);
    MoveBall(dt, rect_ball);
    SDL_RenderPresent(render);
  }
}
