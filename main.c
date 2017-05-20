#include "main.h"
#include "beginScreen.h"
#include "homeScreen.h"

int main(int argc, char* args[] )
{
    FILE *file;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("\nError initializing SDL\n");
        return 0;
    }
    if (TTF_Init() < 0) {
        printf("\nError loading font\n");
        return 0;
    }
    m_window = SDL_CreateWindow("ProjectCruiser", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (m_window == 0) {
        SDL_Quit();
        printf("\nError creating window\n");
        return 0;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == 0){
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        printf("\nError creating renderer\n");
        return 0;
    }
    initiate(file, m_renderer, event, m_window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}

void initiate(FILE*file, SDL_Renderer *m_renderer, SDL_Event event, SDL_Window *m_window) {
    int check;
    check = beginSplash(file, m_renderer, event);
    if (check == 1) {
        return;
    }
    homeSplash(file, m_renderer, event);
    destroyEverything(m_window, m_renderer);
}

void destroyEverything(SDL_Window* m_window, SDL_Renderer* m_renderer) {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}
