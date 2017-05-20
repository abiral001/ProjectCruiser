#include "main.h"
#include "overScreen.h"

int overSplash(FILE *file, SDL_Renderer *m_renderer, SDL_Event event, long int scoreN) {
    int quit = 0;
    TTF_Font *font = TTF_OpenFont("sources/Fonts/DESTROY_.TTF", 70);
    TTF_Font *elsem = TTF_OpenFont("sources/Fonts/segoeui.ttf", 24);
    SDL_Color color = {255, 255, 255, 0};
    SDL_Texture *gameOver, *enter, *score, *back;
    SDL_Rect over, ente, scor;
    SDL_Surface *surface;

    surface = TTF_RenderText_Solid(font, "GAME OVER", color);
    gameOver = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(elsem, "Score = ", color);
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
    scor.y = 570;

    SDL_QueryTexture(gameOver, 0, 0, &over.w, &over.h);
    SDL_QueryTexture(score, 0, 0, &scor.w, &scor.h);
    SDL_QueryTexture(enter, 0, 0, &ente.w, &ente.h);

    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, back, 0, 0);
    SDL_RenderCopy(m_renderer, gameOver, 0, &over);
    SDL_RenderCopy(m_renderer, score, 0, &scor);
    displayScore(m_renderer, scoreN, elsem);
    SDL_RenderCopy(m_renderer, enter, 0, &ente);
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
