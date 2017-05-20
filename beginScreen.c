#include "main.h"
#include "beginScreen.h"

int beginSplash(FILE *file, SDL_Renderer *m_renderer, SDL_Event event) {
     int elapsed = SDL_GetTicks(); // stores time from when SDL was initialized
     SDL_Texture *m_texture, *t_texture; //Creates two variables from which individual pixels of the window
     SDL_Color font_color = {255, 255, 255, 0}; //defines color in Red, green and blue format
     TTF_Font *m_font = TTF_OpenFont("sources/Fonts/segoeui.ttf", 18); //opens font which is located in fonts folder of size 18
     SDL_Surface *surface = TTF_RenderText_Solid(m_font, "Through the joint collaboration of Nidwijja Bhatta, Nihar Karki, Eelisha Pathak and Abiral Pokharel", font_color);
     m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 800, 600);
     t_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
     SDL_FreeSurface(surface);
     SDL_Rect tRect;
     tRect.x = 15;
     tRect.y = 300;
     SDL_QueryTexture(t_texture, 0, 0, &tRect.w, &tRect.h); //width and height of the rectangle where we display the text from surface
     if (m_texture == 0) { // if m_texture is not initailized or gets some error while storing data then t_texture store 0
        printf("\nError creating texture");
        SDL_DestroyRenderer(m_renderer);
        return 1;
     }
     SDL_RenderClear(m_renderer); //clears the memory of renderer(pixel controller)
     SDL_RenderCopy(m_renderer, m_texture, 0, 0); // copies the data of m_texture in the memory
     SDL_RenderCopy(m_renderer, t_texture, 0, &tRect); //copies the data of t_texture in the memory at the location of tRect
     SDL_RenderPresent(m_renderer); //transfers the contents of memory in renderer in the display
     while(elapsed < 5000){ // loops until time spent in the beginscreen is 5 sec
        elapsed = SDL_GetTicks(); // stores new data of elapsed
        while (SDL_PollEvent(&event)) { // if any event happens the this loop is run

            if (event.type == SDL_QUIT){ //if the event is clicked on X mark the program closes
                    SDL_DestroyTexture(m_texture);
                    return 1;
            }
        }
    }
    SDL_DestroyTexture(m_texture); //destroys everything
    SDL_DestroyTexture(t_texture);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
    return 0;
}
