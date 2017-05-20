#include "main.h"
#include "gameScreen.h"

int gameSplash(FILE *file, SDL_Renderer *m_renderer, SDL_Event event) {
    int obstacle = 0, i, instant, lane = 2, count = 0, count2 = 0;
    long int score = 0, speed = 2, mark = 50;
    int choice = getCarColor(file), choice2 = getTrack();
    int randomTruck[2], randomLane, randomX;
    long int timel = SDL_GetTicks(), timel2;
    SDL_Color color = {255,255,255,0};
    TTF_Font *goFont = TTF_OpenFont("sources/Fonts/DESTROY_.ttf", 24);
    SDL_Surface *surface;
    SDL_Texture *road, *road2, *prot, *obs[4], *go[6];
    SDL_Rect roadRect, road2Rect, crop, obsR[4], goR[3], protR;

    srand(time(0));
    randomTruck[0] = rand() % 4;
    randomTruck[1] = rand() % 4;
    randomLane = rand() % 4;

    if (randomTruck[1] == 4) {randomTruck[1] = 1;}

    switch (randomLane) {
    case 0:
        randomX = 120;
        break;
    case 1:
        randomX = 260;
        break;
    case 2:
        randomX = 480;
        break;
    case 3:
        randomX = 540;
        break;
    }

    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);

    surface = TTF_RenderText_Solid(goFont, "3", color);
    go[0] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(goFont, "2", color);
    go[1] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(goFont, "1", color);
    go[2] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(goFont, "GO", color);
    go[3] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(goFont, "Press Escape to return to Main Menu", color);
    go[4] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(goFont, "Score : ", color);
    go[5] = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    switch (choice2) {
    case 0:
        road = IMG_LoadTexture(m_renderer, "sources/Images/iceRoad.png");
        break;
    case 1:
        road = IMG_LoadTexture(m_renderer, "sources/Images/cityRoad.png");
        break;
    default:
        road = IMG_LoadTexture(m_renderer, "sources/Images/desertRoad.png");
        break;
    }

    road2 = road;

    switch (choice) {
    case 0:
        prot = IMG_LoadTexture(m_renderer, "sources/Images/p_redcar.png");
        break;
    case 1:
        prot = IMG_LoadTexture(m_renderer, "sources/Images/p_bluecar.png");
        break;
    case 2:
        prot = IMG_LoadTexture(m_renderer, "sources/Images/p_yellowcar.png");
        break;
    case 3:
        prot = IMG_LoadTexture(m_renderer, "sources/Images/p_greencar.png");
        break;
    }

    obs[0] = IMG_LoadTexture(m_renderer, "sources/Images/o_yellowtruck.png");
    obs[1] = IMG_LoadTexture(m_renderer, "sources/Images/o_redtruck.png");
    obs[2] = IMG_LoadTexture(m_renderer, "sources/Images/o_bluetruck.png");
    obs[3] = IMG_LoadTexture(m_renderer, "sources/Images/o_greentruck.png");

    roadRect.x = roadRect.y = road2Rect.x = 0;
    road2Rect.y = 0;
    crop.x = 0;
    crop.y = 600;
    goR[0].x = goR[0].y = 0;
    goR[1].x = 375;
    goR[1].y = 300;
    goR[2].x = 0;
    goR[2].y = 570;
    protR.x = 400;
    protR.y = 500;
    obsR[0].x = randomX + 120;
    obsR[1].x = randomX;
    obsR[0].y = 0;

    if (obsR[0].x > 540) {obsR[0].x = 120;}

    SDL_QueryTexture(go[5], 0, 0, &goR[2].w, &goR[2].h);
    SDL_QueryTexture(obs[0], 0, 0, &obsR[0].w, &obsR[0].h);
    SDL_QueryTexture(prot, 0, 0, &protR.w, &protR.h);
    SDL_QueryTexture(go[0], 0, 0, &goR[1].w, &goR[1].h);
    SDL_QueryTexture(go[4], 0, 0, &goR[0].w, &goR[0].h);
    SDL_QueryTexture(road, 0, 0, &roadRect.w, &roadRect.h);
    road2Rect.w = roadRect.w;
    road2Rect.h = crop.h = 600-crop.y;
    crop.w = 800;
    obsR[1].w = obsR[0].w;
    obsR[1].h = obsR[0].h;

    while((instant = SDL_GetTicks()-timel) <= 4000) {
                if (instant < 1000) {i = 0;}
                else if (instant < 2000) {i = 1;}
                else if (instant < 3000) {i = 2;}
                else if (instant < 4000) {i = 3;}
                SDL_RenderClear(m_renderer);
                SDL_RenderCopy(m_renderer, road2, &crop, &road2Rect);
                SDL_RenderCopy(m_renderer, road, 0, &roadRect);
                SDL_RenderCopy(m_renderer, go[4], 0, &goR[0]);
                SDL_RenderCopy(m_renderer, go[i], 0, &goR[1]);
                SDL_RenderPresent(m_renderer);
    }

    while(!obstacle){
        crop.y-=speed;
        if (crop.y == -speed) {crop.y = 600;}
        road2Rect.h = 600-crop.y;
        crop.h = road2Rect.h;

        roadRect.y+=speed;
        if(roadRect.y == 600+speed) {roadRect.y = 0;}

        obsR[0].y+=(speed/2);
        obsR[1].y+=(speed/2);

        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, road2, &crop, &road2Rect);
        SDL_RenderCopy(m_renderer, road, 0, &roadRect);
        SDL_RenderCopy(m_renderer, prot, 0, &protR);
        if (obsR[0].y > 600) {count++;}
        if (obsR[1].y > 600) {count2++;}
        SDL_RenderCopy(m_renderer, obs[0], 0, &obsR[1]);
        SDL_RenderCopy(m_renderer, obs[randomTruck[0]], 0, &obsR[0]);
        SDL_RenderCopy(m_renderer, go[5], 0, &goR[2]);
        displayScore(m_renderer, score, goFont);
        SDL_RenderPresent(m_renderer);

        for (i = 0; i < 2; i++) {
            if ((protR.x >= obsR[i].x && protR.x <= obsR[i].x + 135) && (protR.y >= obsR[i].y && protR.y <= obsR[i].y+250)) {
                obstacle = overSplash(file, m_renderer, event, score);
            }
        }

        if (obstacle == 1) {return 1;}
        else if (obstacle == 10) {return 0;}

        if (SDL_GetTicks()-timel > 3000) {
            score += speed*0.5;
            timel = SDL_GetTicks();
        }

        if (score >= mark * 2) {
            mark = score;
            speed+=2;
        }

        if (count == 1) {
            randomTruck[0] = rand() % 4;
            count--;
            obsR[0].x = (rand() % 4)*140 + 120;
            obsR[0].y = 0;
        }

        if (count2 == 1) {
            randomTruck[1] = rand() % 4;
            count2--;
            obsR[1].x = (rand() % 4)*140 + 120;
            obsR[1].y = 0;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                    return 1;
            }
            switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    obstacle = 1;
                    break;
                case SDLK_LEFT:
                    if (lane >= 1) {
                        protR.x -= 140;
                        lane --;
                        //printf("\nx = %d, y = %d", obsR[0].x, obsR[1].x);
                    }
                    break;
                case SDLK_RIGHT:
                    if (lane <=2) {
                        protR.x += 140;
                        lane++;
                        // printf("\nx = %d, y = %d", protR.x, protR.y);
                    }
                    break;
                case SDLK_UP:
                    if (protR.y > 300) {
                        protR.y -= 50;
                    }
                    break;
                case SDLK_DOWN:
                    if (protR.y < 550) {
                        protR.y += 50;
                    }
                    break;
                }
                break;
            default:
                break;
            }
        }
    }
    /*for(i = 0; i< 5; i++) {
        SDL_DestroyTexture(go[i]);
        SDL_DestroyTexture(obs[i]);
    }*/
    SDL_DestroyTexture(prot);
    SDL_DestroyTexture(road);
    SDL_DestroyTexture(road2);
    return 0;
}

int getCarColor(FILE *file) {
    file = fopen("cars.ini", "rb");
    char send;
    int color;
    send = fgetc(file);
    if (send == 'b') {
        color = 1;
    }
    else if (send == 'r') {
        color = 0;
    }
    else if (send == 'y') {
        color = 2;
    }
    else {
        color = 3;
    }
    return color;
}

int getTrack() {
    int elapsed = SDL_GetTicks();
    srand(elapsed);
    return (rand() % 3);
}

int displayScore(SDL_Renderer *m_renderer, long int score, TTF_Font *font) {
    int rem, count = 0, i;
    SDL_Color color = {255, 255, 255, 0};
    SDL_Surface *surface;
    SDL_Rect txRect;
    SDL_Texture *tx[10];
    long int temp = score;

    surface = TTF_RenderText_Solid(font, "0", color);
    tx[0] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "1", color);
    tx[1] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "2", color);
    tx[2] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "3", color);
    tx[3] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "4", color);
    tx[4] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "5", color);
    tx[5] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "6", color);
    tx[6] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "7", color);
    tx[7] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "8", color);
    tx[8] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(font, "9", color);
    tx[9] = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    txRect.x = 200;
    txRect.y = 570;

    SDL_QueryTexture(tx[0], 0, 0, &txRect.w, &txRect.h);

    while (temp != 0) {
        count++;
        temp /= 10;
    }
    temp = score;

    while (temp != 0) {
        rem = temp % 10;
        txRect.x -= 20*count;
        SDL_RenderCopy(m_renderer, tx[rem], 0, &txRect);
        count--;
        temp /= 10;
    }
    for (i = 0; i<10;i++) {
        SDL_DestroyTexture(tx[i]);
    }
    return 0;
}
