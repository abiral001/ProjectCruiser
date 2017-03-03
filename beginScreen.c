#include "main.h"
#include "beginScreen.h"

int beginSplash(SDL_Window *m_window, SDL_Renderer *m_renderer, SDL_Event event) {
     int elapsed = SDL_GetTicks();
     SDL_Texture *m_texture, *t_texture;
     SDL_Color font_color = {255, 255, 255, 0};
     TTF_Font *m_font = TTF_OpenFont("sources/Fonts/segoeui.ttf", 18);
     SDL_Surface *surface = TTF_RenderText_Solid(m_font, "Through the joint collaboration of Nidwijja Bhatta, Nihar Karki, Eelisha Pathak and Abiral Pokharel", font_color);
     m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 800, 600);
     t_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
     SDL_FreeSurface(surface);
     SDL_Rect tRect;
     tRect.x = 15;
     tRect.y = 300;
     SDL_QueryTexture(t_texture, NULL, NULL, &tRect.w, &tRect.h);
     if (m_texture == 0) {
        printf("\nError creating texture");
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        return 1;
     }
     SDL_RenderClear(m_renderer);
     SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
     SDL_RenderCopy(m_renderer, t_texture, NULL, &tRect);
     SDL_RenderPresent(m_renderer);
     while(elapsed < 7000){
        elapsed = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT){
                    SDL_DestroyTexture(m_texture);
                    return 1;
            }
        }
    }
    SDL_DestroyTexture(m_texture);
    SDL_DestroyTexture(t_texture);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
    return 0;
}
