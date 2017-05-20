#include "main.h"
#include "customizeScreen.h"

int customizeSplash(FILE *file, SDL_Renderer *m_renderer, SDL_Event event) {
    int quit = 0, menu = 0;
    file = fopen("cars.ini", "wb");
    TTF_Font *font = TTF_OpenFont("sources/Fonts/segoeui.ttf", 24);
    SDL_Color color = {255, 255, 255, 0};
    SDL_Surface *surface;
    SDL_Texture *backImage, *redCar, *blueCar, *greenCar, *yellowCar, *save, *car, *track, *box;
    SDL_Rect thumbnails, words1, words2, boxRect, boxCrop, saveR, blueR, greenR, yellowR;

    backImage = IMG_LoadTexture(m_renderer, "sources/Images/01titleImage.jpg");
    box = IMG_LoadTexture(m_renderer, "sources/Images/05titleImage.png");
    surface = TTF_RenderText_Solid(font, "Press Enter to Save", color);
    save = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "Customize Cars", color);
    car = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "Customize Tracks", color);
    track = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);
    redCar = IMG_LoadTexture(m_renderer, "sources/Images/p_redcar.png");
    blueCar = IMG_LoadTexture(m_renderer, "sources/Images/p_bluecar.png");
    greenCar = IMG_LoadTexture(m_renderer, "sources/Images/p_greencar.png");
    yellowCar = IMG_LoadTexture(m_renderer, "sources/Images/p_yellowcar.png");

    words1.x = 300;
    words1.y = 150;
    words2.x = 300;
    words2.y = 200;
    boxRect.y = 5;
    boxRect.x = 250;
    boxRect.w = 200;
    boxRect.h = 170;
    boxCrop.x = 250;
    boxCrop.y = 200;
    boxCrop.w = 800;
    boxCrop.h = 200;
    saveR.x = 0;
    saveR.y = 500;

    SDL_QueryTexture(save, 0, 0, &saveR.w, &saveR.h);
    SDL_QueryTexture(car, 0, 0, &words1.w, &words1.h);
    SDL_QueryTexture(track, 0, 0, &words2.w, &words2.h);

    thumbnails.x = blueR.x = yellowR.x = greenR.x = 300;
    thumbnails.y = 50;
    blueR.y = 180;
    yellowR.y = 310;
    greenR.y = 440;
    thumbnails.w = 500;
    blueR.w = 500;
    yellowR.w = 500;
    greenR.w = 500;
    thumbnails.h = 500;
    blueR.h = 500;
    yellowR.h = 500;
    greenR.h = 500;

    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, backImage, 0, 0);
    SDL_RenderCopy(m_renderer, redCar, 0, &thumbnails);
    SDL_RenderCopy(m_renderer, blueCar, 0, &blueR);
    SDL_RenderCopy(m_renderer, yellowCar, 0, &yellowR);
    SDL_RenderCopy(m_renderer, greenCar, 0, &greenR);
    SDL_RenderCopy(m_renderer, box, &boxCrop, &boxRect);
    SDL_RenderPresent(m_renderer);

    while(!quit) {
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                case SDLK_DOWN:
                    if (menu !=3) {
                        menu++;
                        boxRect.y += 130;
                        SDL_RenderClear(m_renderer);
                        SDL_RenderCopy(m_renderer, backImage, 0, 0);
                        SDL_RenderCopy(m_renderer, redCar, 0, &thumbnails);
                        SDL_RenderCopy(m_renderer, blueCar, 0, &blueR);
                        SDL_RenderCopy(m_renderer, yellowCar, 0, &yellowR);
                        SDL_RenderCopy(m_renderer, greenCar, 0, &greenR);
                        SDL_RenderCopy(m_renderer, box, &boxCrop, &boxRect);
                        SDL_RenderPresent(m_renderer);
                    }
                    break;
                case SDLK_UP:
                    if (menu != 0) {
                        menu--;
                        boxRect.y -=130;
                        SDL_RenderClear(m_renderer);
                        SDL_RenderCopy(m_renderer, backImage, 0, 0);
                        SDL_RenderCopy(m_renderer, redCar, 0, &thumbnails);
                        SDL_RenderCopy(m_renderer, blueCar, 0, &blueR);
                        SDL_RenderCopy(m_renderer, yellowCar, 0, &yellowR);
                        SDL_RenderCopy(m_renderer, greenCar, 0, &greenR);
                        SDL_RenderCopy(m_renderer, box, &boxCrop, &boxRect);
                        SDL_RenderPresent(m_renderer);
                    }
                    break;
                case SDLK_RETURN:
                    switch (menu) {
                    case 0:
                        fprintf(file, "r");
                        break;
                    case 1:
                        fprintf(file, "b");
                        break;
                    case 2:
                        fprintf(file, "y");
                        break;
                    case 3:
                        fprintf(file, "g");
                        break;
                    default:
                        fprintf(file, "b");
                        break;
                    }
                    break;
                case SDLK_BACKSPACE:
                    SDL_DestroyTexture(backImage);
                    fclose(file);
                    return 0;
                    break;
                }
                break;
            }
        }
    }
    fclose(file);
    SDL_DestroyTexture(backImage);
    SDL_DestroyTexture(save);
    SDL_DestroyTexture(redCar);
    SDL_DestroyTexture(blueCar);
    SDL_DestroyTexture(yellowCar);
    SDL_DestroyTexture(greenCar);
    return 1;
}
