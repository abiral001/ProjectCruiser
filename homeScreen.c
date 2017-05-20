#include "main.h"
#include "homeScreen.h"
#include "gameScreen.h"
#include "creditsScreen.h"
#include "customizeScreen.h"
#include "overScreen.h"

int homeSplash(FILE *file, SDL_Renderer *m_renderer, SDL_Event event) {
    SDL_Rect rect, crop, nameRect, nameCrop, tRect, cRect, cuRect, eRect, boxRect, boxCrop;
    SDL_Color text_color = {0, 255, 255, 0};
    SDL_Color title_color = {0, 0, 100, 0};
    TTF_Font *textFont = TTF_OpenFont("sources/Fonts/boul.ttf", 40);
    TTF_Font *titleFont = TTF_OpenFont("sources/Fonts/DESTROY_.TTF", 65);
    SDL_Surface *playSurface;
    int quit = 0, menu = 0;
    SDL_Texture *image, *titleImage, *playText, *customizeText, *creditsText, *exitText, *box;

    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);

    image = IMG_LoadTexture(m_renderer, "sources/Images/01titleImage.jpg");
    box = IMG_LoadTexture(m_renderer, "sources/Images/05titleImage.png");
    playSurface = TTF_RenderText_Solid(titleFont, "Project CRUISER", title_color);
    titleImage = SDL_CreateTextureFromSurface(m_renderer, playSurface);
    playSurface = TTF_RenderText_Solid(textFont, "Play Now!", text_color);
    playText = SDL_CreateTextureFromSurface(m_renderer, playSurface);
    playSurface = TTF_RenderText_Solid(textFont, "Customize Car", text_color);
    customizeText = SDL_CreateTextureFromSurface(m_renderer, playSurface);
    playSurface = TTF_RenderText_Solid(textFont, "Credits", text_color);
    creditsText = SDL_CreateTextureFromSurface(m_renderer, playSurface);
    playSurface = TTF_RenderText_Solid(textFont, "Quit", text_color);
    exitText = SDL_CreateTextureFromSurface(m_renderer, playSurface);

    if (image <= 0 || titleImage <= 0 || box <= 0) {
        IMG_Quit();
        return 0;
    }

    tRect.x = cRect.x = cuRect.x = eRect.x = 15;
    tRect.y = 300;
    cuRect.y = 350;
    cRect.y = 400;
    eRect.y = 450;
    boxRect.y = 290;
    boxRect.x = 0;
    boxRect.w = 500;
    boxRect.h = 100;
    rect.x = 0;
    rect.y = 0;
    nameRect.x = 20;
    nameRect.y = 20;
    rect.w = 800;
    rect.h = 600;
    crop.x = nameCrop.x = 0;
    crop.y = nameCrop.y = 0;
    boxCrop.x = 250;
    boxCrop.y = 200;
    boxCrop.w = 800;
    boxCrop.h = 600;

    SDL_QueryTexture(playText, 0, 0, &tRect.w, &tRect.h);
    SDL_QueryTexture(customizeText, 0, 0, &cuRect.w, &cuRect.h);
    SDL_QueryTexture(creditsText, 0, 0, &cRect.w, &cRect.h);
    SDL_QueryTexture(exitText, 0, 0, &eRect.w, &eRect.h);
    SDL_QueryTexture(image, 0, 0, &crop.w, &crop.h);
    SDL_QueryTexture(titleImage, 0, 0, &nameRect.w, &nameRect.h);

    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, image, &crop, &rect);
    SDL_RenderCopy(m_renderer, titleImage, 0, &nameRect);
    SDL_RenderCopy(m_renderer, playText, 0, &tRect);
    SDL_RenderCopy(m_renderer, customizeText, 0, &cuRect);
    SDL_RenderCopy(m_renderer, creditsText, 0, &cRect);
    SDL_RenderCopy(m_renderer, exitText, 0, &eRect);
    SDL_RenderCopy(m_renderer, box, &boxCrop, &boxRect);
    SDL_RenderPresent(m_renderer);

    while(!quit){
        srand(time(0));
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                    quit = 1;
            }
            switch(event.type) {
            case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                    case SDLK_DOWN:
                        if (menu != 3) {
                            menu++;
                            boxRect.y += 50;
                            SDL_RenderClear(m_renderer);
                            SDL_RenderCopy(m_renderer, image, &crop, &rect);
                            SDL_RenderCopy(m_renderer, titleImage, 0, &nameRect);
                            SDL_RenderCopy(m_renderer, playText, 0, &tRect);
                            SDL_RenderCopy(m_renderer, customizeText, 0, &cuRect);
                            SDL_RenderCopy(m_renderer, creditsText, 0, &cRect);
                            SDL_RenderCopy(m_renderer, exitText, 0, &eRect);
                            SDL_RenderCopy(m_renderer, box, &boxCrop, &boxRect);
                            SDL_RenderPresent(m_renderer);
                        }
                        break;
                    case SDLK_UP:
                        if (menu != 0) {
                            menu--;
                            boxRect.y -= 50;
                            SDL_RenderClear(m_renderer);
                            SDL_RenderCopy(m_renderer, image, &crop, &rect);
                            SDL_RenderCopy(m_renderer, titleImage, 0, &nameRect);
                            SDL_RenderCopy(m_renderer, playText, 0, &tRect);
                            SDL_RenderCopy(m_renderer, customizeText, 0, &cuRect);
                            SDL_RenderCopy(m_renderer, creditsText, 0, &cRect);
                            SDL_RenderCopy(m_renderer, exitText, 0, &eRect);
                            SDL_RenderCopy(m_renderer, box, &boxCrop, &boxRect);
                            SDL_RenderPresent(m_renderer);
                        }
                        break;
                    case SDLK_RETURN:
                        switch(menu) {
                        case 0:
                            quit = gameSplash(file, m_renderer, event);
                            break;
                        case 1:
                            quit = customizeSplash(file, m_renderer, event);
                            break;
                        case 2:
                            quit = creditsSplash(file, m_renderer, event);
                            break;
                        case 3:
                            quit = 1;
                            break;
                        }
                    }
                    break;
            default:
                    break;
            }
        }
    }

    SDL_DestroyTexture(image);
    SDL_DestroyTexture(titleImage);
    SDL_DestroyTexture(playText);
    SDL_DestroyTexture(customizeText);
    SDL_DestroyTexture(creditsText);

    return 0;
}

