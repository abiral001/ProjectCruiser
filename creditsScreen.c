#include "main.h"
#include "creditsScreen.h"

int creditsSplash(SDL_Window *m_window, SDL_Renderer *m_renderer, SDL_Event event) {
    int quit = 0, i;
     SDL_Texture *m_texture, *t_texture, *t2, *t3, *t4, *t5, *t6, *t7, *t8;
     SDL_Color font_color = {255, 255, 0, 0};
     TTF_Font *m_font = TTF_OpenFont("sources/Fonts/segoeui.ttf", 12);
     SDL_Surface *surface = TTF_RenderText_Solid(m_font, "Programmers : ", font_color);
     SDL_Surface *s2, *s3, *s4, *s5, *s6, *s7, *s8;
     SDL_Rect tRect[8];

     s2 = TTF_RenderText_Solid(m_font, "1. Abiral Pokharel", font_color);
     s3 = TTF_RenderText_Solid(m_font, "2. Eelisha Pathak", font_color);
     s4 = TTF_RenderText_Solid(m_font, "3. Nidwijja Bhatta", font_color);
     s5 = TTF_RenderText_Solid(m_font, "4. Nihar Karki", font_color);
     s6 = TTF_RenderText_Solid(m_font, "The program was made entirely in C programming language with additional API derived from SDL2 which is freely distributed.", font_color);
     s7 = TTF_RenderText_Solid(m_font, "Title Screen image was taken from : https://www.pexels.com/search/car/", font_color);
     s8 = TTF_RenderText_Solid(m_font, "This program can be freely edited and distributed around using its source code at Github", font_color);

     m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 800, 600);
     t_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
     t2 = SDL_CreateTextureFromSurface(m_renderer, s2);
     t3 = SDL_CreateTextureFromSurface(m_renderer, s3);
     t4 = SDL_CreateTextureFromSurface(m_renderer, s4);
     t5 = SDL_CreateTextureFromSurface(m_renderer, s5);
     t6 = SDL_CreateTextureFromSurface(m_renderer, s6);
     t7 = SDL_CreateTextureFromSurface(m_renderer, s7);
     t8 = SDL_CreateTextureFromSurface(m_renderer, s8);

     SDL_FreeSurface(surface);
     SDL_FreeSurface(s2);
     SDL_FreeSurface(s3);
     SDL_FreeSurface(s4);
     SDL_FreeSurface(s5);
     SDL_FreeSurface(s6);
     SDL_FreeSurface(s7);
     SDL_FreeSurface(s8);
     for (i = 0; i<8; i++) {
        tRect[i].x = 0;
        tRect[i].y = 50*i;
     }
     SDL_QueryTexture(t_texture, NULL, NULL, &tRect[0].w, &tRect[0].h);
     SDL_QueryTexture(t2, NULL, NULL, &tRect[1].w, &tRect[1].h);
     SDL_QueryTexture(t3, NULL, NULL, &tRect[2].w, &tRect[2].h);
     SDL_QueryTexture(t4, NULL, NULL, &tRect[3].w, &tRect[3].h);
     SDL_QueryTexture(t5, NULL, NULL, &tRect[4].w, &tRect[4].h);
     SDL_QueryTexture(t6, NULL, NULL, &tRect[5].w, &tRect[5].h);
     SDL_QueryTexture(t7, NULL, NULL, &tRect[6].w, &tRect[6].h);
     SDL_QueryTexture(t8, NULL, NULL, &tRect[7].w, &tRect[7].h);

     if (m_texture == 0) {
        printf("\nError creating texture");
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        return 1;
     }
     SDL_RenderClear(m_renderer);
     SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
     SDL_RenderCopy(m_renderer, t_texture, NULL, &tRect[0]);
     SDL_RenderCopy(m_renderer, t2, NULL, &tRect[1]);
     SDL_RenderCopy(m_renderer, t3, NULL, &tRect[2]);
     SDL_RenderCopy(m_renderer, t4, NULL, &tRect[3]);
     SDL_RenderCopy(m_renderer, t5, NULL, &tRect[4]);
     SDL_RenderCopy(m_renderer, t6, NULL, &tRect[5]);
     SDL_RenderCopy(m_renderer, t7, NULL, &tRect[6]);
     SDL_RenderCopy(m_renderer, t8, NULL, &tRect[7]);


     SDL_RenderPresent(m_renderer);
    while(!quit){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                    quit = 1;
            }
            switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                case SDLK_BACKSPACE:
                    SDL_DestroyTexture(t_texture);
                    SDL_DestroyTexture(t2);
                    SDL_DestroyTexture(t3);
                    SDL_DestroyTexture(t4);
                    SDL_DestroyTexture(t5);
                    SDL_DestroyTexture(t6);
                    SDL_DestroyTexture(t7);
                    SDL_DestroyTexture(t8);
                    return 0;
                    break;
                }
                break;
            default:
                break;
            }
        }
    }
    SDL_DestroyTexture(t_texture);
    SDL_DestroyTexture(t2);
    SDL_DestroyTexture(t3);
    SDL_DestroyTexture(t4);
    SDL_DestroyTexture(t5);
    SDL_DestroyTexture(t6);
    SDL_DestroyTexture(t7);
    SDL_DestroyTexture(t8);
    return 1;
}
