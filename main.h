#ifndef MAIN_H_
#define MAIN_H_
#include <stdio.h>
#include <string.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
void destroyEverything(SDL_Window *, SDL_Renderer *);
void initiate(FILE*, SDL_Renderer*, SDL_Event, SDL_Window*);

#endif // MAIN_H_
