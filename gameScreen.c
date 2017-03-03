#include "main.h"
#include "gameScreen.h"

int gameSplash(SDL_Window *m_window, SDL_Renderer *m_renderer, SDL_Event event) {
    int obstacle = 0, i, instant, lane = 2, count = 0, count2 = 0;
    int randomTruck[2], randomLane, randomX;
    long int timel = SDL_GetTicks();
    SDL_Color color = {255,255,255,0};
    TTF_Font *goFont = TTF_OpenFont("sources/Fonts/DESTROY_.ttf", 24);
    SDL_Surface *surface;
    SDL_Texture *road, *road2, *prot, *obs[4], *go[5];
    SDL_Rect roadRect, road2Rect, crop, obsR[4], goR[3], protR;

    srand(time(0));
    randomTruck[0] = rand() % 4;
    randomTruck[1] = rand() % 4 +1;
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
    surface = TTF_RenderText_Solid(goFont, "GO!", color);
    go[3] = SDL_CreateTextureFromSurface(m_renderer, surface);
    surface = TTF_RenderText_Solid(goFont, "Press Escape to return to Main Menu", color);
    go[4] = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    road = IMG_LoadTexture(m_renderer, "sources/Images/cityRoad.png");
    road2 = road;
    prot = IMG_LoadTexture(m_renderer, "sources/Images/p_bluecar.png");
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
    protR.x = 400;
    protR.y = 500;
    obsR[0].x = randomX + 120;
    obsR[1].x = randomX;
    obsR[0].y = 0;

    if (obsR[0].x > 540) {obsR[0].x = 120;}

    SDL_QueryTexture(obs[0], NULL, NULL, &obsR[0].w, &obsR[0].h);
    SDL_QueryTexture(prot, NULL, NULL, &protR.w, &protR.h);
    SDL_QueryTexture(go[0], NULL, NULL, &goR[1].w, &goR[1].h);
    SDL_QueryTexture(go[4], NULL, NULL, &goR[0].w, &goR[0].h);
    SDL_QueryTexture(road, NULL, NULL, &roadRect.w, &roadRect.h);
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
                SDL_RenderCopy(m_renderer, road, NULL, &roadRect);
                SDL_RenderCopy(m_renderer, go[4], NULL, &goR[0]);
                SDL_RenderCopy(m_renderer, go[i], NULL, &goR[1]);
                SDL_RenderPresent(m_renderer);
    }

    while(!obstacle){
        if (SDL_GetTicks() - timel > 0) {
                crop.y-=2;
                if (crop.y == -2) {crop.y = 600;}
                road2Rect.h = 600-crop.y;
                crop.h = road2Rect.h;

                roadRect.y+=2;
                if(roadRect.y == 602) {roadRect.y = 0;}

                obsR[0].y++;
                obsR[1].y++;
                SDL_RenderClear(m_renderer);
                SDL_RenderCopy(m_renderer, road2, &crop, &road2Rect);
                SDL_RenderCopy(m_renderer, road, NULL, &roadRect);
                SDL_RenderCopy(m_renderer, prot, NULL, &protR);
                if (obsR[0].y > 600) {count++;}
                if (obsR[1].y > 600) {count2++;}
                SDL_RenderCopy(m_renderer, obs[randomTruck[1]], NULL, &obsR[1]);
                SDL_RenderCopy(m_renderer, obs[randomTruck[0]], NULL, &obsR[0]);
                SDL_RenderPresent(m_renderer);
                timel = SDL_GetTicks();
        }

        if ((protR.x == obsR[0].x || protR.x <= obsR[0].x + 60) && (protR.y >= obsR[0].y && protR.y <= obsR[0].y+250)) {
            obstacle = overSplash(m_window, m_renderer, event);
        }
        if ((protR.x == obsR[1].x || protR.x <= obsR[1].x + 60) && (protR.y >= obsR[1].y && protR.y <= obsR[1].y+250)) {
            obstacle = overSplash(m_window, m_renderer, event);
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
        if (obstacle == 1) {return 1;}
        else if (obstacle == 10) {return 0;}
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

