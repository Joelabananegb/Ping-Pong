#include "game.h"

/****************************************
 *                                      *
 *    TODO Score show                   *
 *    TODO racket movement              *
 *    TODO Ball and racket collision    *
 *    TODO Scoring                      *
 *    TODO Game over                    *
 *                                      *
 ****************************************/

void Log(const char *log)
{
  SDL_Log("Erreur: %s", log);
}

int running = 1;

GameStruct *Init(SDL_Window *window, SDL_Renderer *render, TTF_Font *font)
{
  int width, height;
  SDL_GetWindowSize(window, &width, &height);

  GameStruct *game = malloc(sizeof(GameStruct));
  if (game==NULL) return NULL;

  game->left         = (SDL_Rect){RACKET_PADDING + 10, (height/ 2) - BALL_SIZE*2, RACKET_PADDING, BALL_SIZE*6};
  game->right        = (SDL_Rect){width - 30, (height/ 2) - BALL_SIZE*2, RACKET_PADDING, BALL_SIZE*6};
  game->ball         = (SDL_Rect){(width - BALL_SIZE) / 2, (height- BALL_SIZE) / 2, BALL_SIZE, BALL_SIZE};
  game->dots         = (SDL_Rect){(width - 5)/2, 0, 5, LINE_HEIGHT};

  game->ball_x       = 100.0;
  game->ball_y       = 100.0;
  game->left_y       = 0.0;
  game->left_score   = 0;
  game->right_score  = 0;

  game->dx           = 1;
  game->dy           = -1;

  game->window       = window;
  game->render       = render;
  game->font         = font;
  game->line_length  = ((height / 100)*(height/ 100))+2;

  return game;
}

void Update(GameStruct *gameStruct)
{
  int width, height;
  SDL_GetWindowSize(gameStruct->window, &width, &height);

  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){

      gameStruct->w            = event.window.data1;
      gameStruct->h            = event.window.data2;

      gameStruct->left.x       = RACKET_PADDING + 10;
      gameStruct->left.y       = (gameStruct->h/ 2) - BALL_SIZE*2;
      gameStruct->left.w       = RACKET_PADDING;
      gameStruct->left.h       = BALL_SIZE*6;

      gameStruct->right.x      = gameStruct->w- 30;
      gameStruct->right.y      = (gameStruct->h/ 2) - BALL_SIZE*2;
      gameStruct->right.w      = RACKET_PADDING;
      gameStruct->right.h      = BALL_SIZE*6;

      gameStruct->ball.x       = (gameStruct->w- BALL_SIZE) / 2;
      gameStruct->ball.y       = (gameStruct->h- BALL_SIZE) / 2;
      gameStruct->ball.w       = BALL_SIZE;
      gameStruct->ball.h       = BALL_SIZE;

      gameStruct->dots.x       = (gameStruct->w - 5) / 2;
      gameStruct->dots.y       = 0;
      gameStruct->dots.w       = 5;
      gameStruct->dots.h       = LINE_HEIGHT;
      gameStruct->line_length  = ((gameStruct->h / 100)*(gameStruct->h/ 100))+2;
    }

    if (event.type == SDL_QUIT){
      running = 0;
    }
  }

  if (keystate[SDL_SCANCODE_UP] && gameStruct->left.y > 0){
    gameStruct->left.y -= (int)(SPEED*1.2 * gameStruct->deltatime);
  }

  if (keystate[SDL_SCANCODE_DOWN] && gameStruct->left.y < gameStruct->h - BALL_SIZE*6){
    gameStruct->left.y += (int)(SPEED * 1.2 * gameStruct->deltatime);
  }

  if (keystate[SDL_SCANCODE_E] && gameStruct->right.y > 0){
    gameStruct->right.y -= (int)(SPEED * 1.2 * gameStruct->deltatime);
  }

  if (keystate[SDL_SCANCODE_D] && gameStruct->right.y < gameStruct->h - BALL_SIZE*6){
    gameStruct->right.y += (int)(SPEED * 1.2 * gameStruct->deltatime);
  }
}

void Draw(GameStruct *gameStruct)
{
  SDL_SetRenderDrawColor(gameStruct->render, 255, 255, 255, 255);

  SDL_RenderFillRect(gameStruct->render, &gameStruct->ball);
  SDL_RenderFillRect(gameStruct->render, &gameStruct->left);
  SDL_RenderFillRect(gameStruct->render, &gameStruct->right);


  for (int i = 0; i <= gameStruct->line_length; i++){
    if (i%2 == 0){
      gameStruct->dots.y = i*LINE_HEIGHT;
      SDL_RenderFillRect(gameStruct->render, &gameStruct->dots);
    }
  }
}

void MoveBall(GameStruct *gameStruct)
{
    gameStruct->ball_x += gameStruct->dx * SPEED *0.5 * gameStruct->deltatime;
    gameStruct->ball_y += gameStruct->dy * SPEED *0.5 * gameStruct->deltatime;

    if (gameStruct->ball_x < 0){
        gameStruct->ball_x = 0;
        printf("%.2lf\n",gameStruct->ball_x);
        gameStruct->dx     = -gameStruct->dx;

        gameStruct->ball.x       = (gameStruct->w- BALL_SIZE) / 2;
        gameStruct->ball.y       = (gameStruct->h- BALL_SIZE) / 2;
        gameStruct->left_score++;  
    }else if (gameStruct->ball_x > gameStruct->w - gameStruct->ball.w){
        gameStruct->ball_x = gameStruct->w - gameStruct->ball.w;
        gameStruct->dx     = -gameStruct->dx;
    }else{
      gameStruct->ball.x = (int)lround(gameStruct->ball_x);
    }

    if (gameStruct->ball_y < 0){
        gameStruct->ball_y = 0;
        gameStruct->dy     = -gameStruct->dy;

    }else if (gameStruct->ball_y > gameStruct->h - gameStruct->ball.h){
        gameStruct->ball_y = gameStruct->h - gameStruct->ball.h;
        gameStruct->dy     = -gameStruct->dy;
    }else{
  
      gameStruct->ball.y = (int)lround(gameStruct->ball_y);
    }

}

void RenderScore(GameStruct *gameStruct){
  char score[128];
  char space[10];
  for (int i = 0; i<8;i++){
    space[i]=32;
  }
  sprintf(score, "%d%s%d", gameStruct->left_score,space,gameStruct->right_score);
  SDL_Color color = {255,255,255,255};
  SDL_Surface *fontSurf = TTF_RenderText_Blended(gameStruct->font,score,color);
  SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(gameStruct->render, fontSurf);
  SDL_FreeSurface(fontSurf);

  SDL_Rect fontRect = {gameStruct->w/2 - 32*4, 50, 0, 0};
  SDL_QueryTexture(fontTexture, NULL, NULL, &fontRect.w, &fontRect.h);
  SDL_RenderCopy(gameStruct->render,fontTexture, NULL, &fontRect);
  SDL_DestroyTexture(fontTexture);
}

void Game(SDL_Renderer *render, SDL_Window *window, TTF_Font *font)
{
  GameStruct *gameStruct = Init(window, render, font);
  Uint64 now             = SDL_GetPerformanceCounter();
  Uint64 last            = 0;

  while(running){
    last                  = now;
    now                   = SDL_GetPerformanceCounter();
    gameStruct->deltatime = (double)(now-last)*1000/(double)SDL_GetPerformanceFrequency();

    Update(gameStruct);
    SDL_SetRenderDrawColor(gameStruct->render, 19, 19, 24, 255);
    SDL_RenderClear(gameStruct->render);
    RenderScore(gameStruct);
    Draw(gameStruct);
    MoveBall(gameStruct);
    SDL_RenderPresent(gameStruct->render);
  }

  free(gameStruct);
}
