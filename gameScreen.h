#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_
int gameSplash(FILE*, SDL_Renderer*, SDL_Event);
int getCarColor(FILE *);
int getTrack();
int displayScore(SDL_Renderer*, long int, TTF_Font*);
#endif // GAMESCREEN_H_
