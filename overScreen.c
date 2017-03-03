#include "main.h"
#include "overScreen.h"

int overSplash(SDL_Window *m_window, SDL_Renderer *m_renderer, SDL_Event event) {
    int quit = 0;
    TTF_Font *font = TTF_OpenFont("sources/Fonts/DESTROY_.TTF", 70);
    TTF_Font *elsem = TTF_OpenFont("sources/Fonts/segoeui.ttf", 24);
    SDL_Color color = {255, 255, 255, 0};
    SDL_Texture *gameOver, *enter, *score, *back;
    SDL_Rect over, ente, scor;
    SDL_Surface *surface;

    surface = TTF_RenderText_Solid(font, "GAME OVER", color);
    gameOver = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(elsem, "Score : 000000", color);
    score = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(elsem, "Press Enter to go to main Menu", color);
    enter = SDL_CreateTextureFromSurface(m_renderer, surface);
    back = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 800, 600);
    SDL_FreeSurface(surface);

    over.x = 175;
    over.y = 300;
    ente.x = 0;
    ente.y = 0;
    scor.x = 0;
    scor.y = 490;

    SDL_QueryTexture(gameOver, NULL, NULL, &over.w, &over.h);
    SDL_QueryTexture(score, NULL, NULL, &scor.w, &scor.h);
    SDL_QueryTexture(enter, NULL, NULL, &ente.w, &ente.h);

    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, back, NULL, NULL);
    SDL_RenderCopy(m_renderer, gameOver, NULL, &over);
    SDL_RenderCopy(m_renderer, score, NULL, &scor);
    SDL_RenderCopy(m_renderer, enter, NULL, &ente);
    SDL_RenderPresent(m_renderer);
    while(!quit){
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT){
                    quit = 1;
            }
            switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                case SDLK_RETURN:
                    return 10;
                }
                break;
            }
        }
    }
    SDL_DestroyTexture(back);
    SDL_DestroyTexture(enter);
    SDL_DestroyTexture(score);
    SDL_DestroyTexture(gameOver);
    return 1;
}
